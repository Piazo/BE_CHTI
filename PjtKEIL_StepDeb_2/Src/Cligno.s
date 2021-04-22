	PRESERVE8
	THUMB   

	include driver/DriverJeuLaser.inc
	export 	timer_callback

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
FlagCligno dcb 0;
	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_Clear(1);
;	}
		


timer_callback proc
	push{lr}
; si flagcligno==1
	ldr r1,=FlagCligno
	ldrb r0,[r1]
	adds r0,r0
	beq Sinon
Alors
;on passe r0 a 0 et on le store dans r1 puis on repasse r0 a 1 puisque cest ce que GPIOB va prendre en argument et a la fin on saute directement a finsi psk on veut pas executer le sinon
	movs r0,#0
	strb r0,[r1]
	movs r0,#1
	bl GPIOB_Set
	b FinSi
Sinon
;on passe la valeur de r0 a 1 et on le store dans flagcligno qui est dans r1 puis on appelle la dct GPIOB_Clear
	movs r0,#1
	strb r0,[r1]
	bl GPIOB_Clear
FinSi
	pop{lr}
	bx lr
	endp

		
		
	END