
#include "DriverJeuLaser.h"
#include <math.h>
#define pi 3.14159265358979323846

extern int DFT_ModuleAuCarre(short int*, char);
extern short int LeSignal[];
int resultat[64];
short int dma_buf[64];

/*
void CallBackSystick(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(int k = 0;k<64;k++){
		resultat[k] = DFT_ModuleAuCarre(dma_buf, k);
	}
}
*/

int main(void){
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
/*
	Systick_Period_ff(360000);
	Systick_Prio_IT(0, CallBackSystick);
	SysTick_On;
	SysTick_Enable_IT;
		
	Init_TimingADC_ActiveADC_ff(ADC1, 72);
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
*/
//============================================================================	
	


//int k[6]={17,18,19,20,23,24}; //ca correspond aux frequence de tir des pistolets divises par 5000

for(int k = 0;k<64;k++){
		resultat[k] = DFT_ModuleAuCarre(LeSignal, k);
	}
	
while	(1)
	{

	}
}

