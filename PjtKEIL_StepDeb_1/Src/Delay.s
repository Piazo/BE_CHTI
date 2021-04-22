	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite


VarTime	dcd 0 ;on dedie une place memoire de 32 bit
	EXPORT	VarTime
	
; ===============================================================================================
	
;constantes (équivalent du #define en C)
TimeValue	equ 900000


	EXPORT Delay_100ms ; la fonction Delay_100ms est rendue publique donc utilisable par d'autres modules.

		
;Section ROM code (read only) :		
	area    moncode,code,readonly
		


; REMARQUE IMPORTANTE 
; Cette manière de créer une temporisation n'est clairement pas la bonne manière de procéder :
; - elle est peu précise
; - la fonction prend tout le temps CPU pour... ne rien faire...
;
; Pour autant, la fonction montre :
; - les boucles en ASM
; - l'accés écr/lec de variable en RAM
; - le mécanisme d'appel / retour sous programme
;
; et donc possède un intérêt pour débuter en ASM pur

Delay_100ms proc
	
	    ldr r0,=VarTime ;on stocke VarTime dans R0
						  
		ldr r1,=TimeValue ;Pareil pour TimeValue dans R1
		str r1,[r0] ;On set VarTime a 900000 dans R0
		
BoucleTempo	
		ldr r1,[r0] ;on charge VarTime qui vaut maintenant 900k
						
		subs r1,#1 ;on fait -1 a VarTime (on commence a decrementer la boucle)
		str  r1,[r0] ;on stocke la nouvelle valeur de VarTime
		bne	 BoucleTempo ;On revient a boucle tempo si VarTime est different de 0, si il vaut 0 alors on sort de BoucleTempo
			
		bx lr ;fin de la fonction, a ciao bonsoir
		endp
		
		
	END	