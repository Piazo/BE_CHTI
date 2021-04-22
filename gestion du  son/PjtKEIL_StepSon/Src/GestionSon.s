	PRESERVE8
	THUMB   

	include driver/DriverJeuLaser.inc
	export CallBackSon
	import Son
	import LongueurSon
	export SortieSon
	export StartSon

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
SortieSon dcw 0
Index dcd 0
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici

StartSon
	ldr r0,=Index
	mov r1, #0
	str r1, [r0]
	bx lr
	endp


CallBackSon proc
	push {r4,r5,r6}
	ldr r0,=Index
	ldr r1,=SortieSon
	ldr r2,=Son
	ldr r3,=LongueurSon
	mov r7, #2
	ldr r4,[r0]
	ldr r3, [r3]
	mul r3, r7
	subs r3,r4
	beq FinSi
Si
	ldrsh r5, [r2,r4, LSL#1]
	mov r6, #719 ;on multiplie d'abord par 719 pour eviter tout probleme lorsqu'on decalera de 16 bits a droite
	add r5, #32768 ;on ajoute 32768 pour avoir que des nb compris entre 0 et 65535
	mul r5,r6
	asr r5, #16 ;on fait A LA FIN le decalage de 16 bits (si on la fait avant on va avoir que des 0)
	strh r5, [r1]
	
	push {r0,r1,r2,r3, lr}
	mov r0,r5
	bl PWM_Set_Value_TIM3_Ch3
	pop {r0,r1,r2,r3, lr}
	
	add r4, #1
	str r4, [r0]	
FinSi
	pop{r4,r5,r6}
	bx lr
	endp
		
		
		
	END	