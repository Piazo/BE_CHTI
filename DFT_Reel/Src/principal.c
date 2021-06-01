#include "DriverJeuLaser.h"
#include <math.h>
#include "GestionSon.h"
#include "Affichage_Valise.h"

extern int DFT_ModuleAuCarre(short int*, char);
extern short int LeSignal[];
int resultatDFT[6];
short int dma_buf[64];
char k[6]={17,18,19,20,23,24}; //ca correspond aux frequence de tir des pistolets divises par 5000
char score[6] = {0,0,0,0,0,0}; //tableau des scores des joueurs
char compte[6] = {0,0,0,0,0,0}; //nb d'occurences des signaux sur la periode d'activite du laser


void CallBackSystick(){
	
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	for(int i = 0;i<6;i++){
		//recuperation de la DFT
		resultatDFT[i] = DFT_ModuleAuCarre(dma_buf, k[i]);
		
		//si on recoit le signal alors on incremente compte de 1
		if ( resultatDFT[i] >= 0x987 ){
			compte[i]++;
		}else{
			compte[i]=0; //sinon on le remet a zero
		}
		
		if( compte[i] == 12 && score[i] < 99){
			score[i]++; //on incremente le score
			StartSon(); //et on joue le petit son
		}
		
		if (i < 4){
			Prepare_Afficheur(i+1, score[i]); //on choisit d'afficher uniquement le score des 4 frequences les plus faible du pistolet laser puisqu'il n'y a que 4 afficheurs
		}
	}
}


int main(void){
// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();

	//----PARTIE DFT ET DMA----//
	//periodicite set a 5ms et configuration du CallBackSystick
	Systick_Period_ff(360000);
	Systick_Prio_IT(1, CallBackSystick);
	SysTick_On;
	SysTick_Enable_IT;
		
	//----TIMER 2 : reglage de la duree de capture du signal, de la pin d'entree et config du TIM2----//
	Init_TimingADC_ActiveADC_ff(ADC1, 72);
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
	
	//----PARTIE SON----//
	//initialisation du timer 4 en pour gerer le debordement du TIMER4 qui active callbackson
	Timer_1234_Init_ff(TIM4,6552);
	Active_IT_Debordement_Timer(TIM4, 2, CallBackSon);
	
	// Reglage de la PWM de frequence 100kHz
	PWM_Init_ff(TIM3, 3, 720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
	//REGLAGE DE L'AFFICHAGE//
	//preparation des afficheurs
	Init_Affichage();
	for(int i=1; i<5; i++){
		Prepare_Afficheur(i, 0);
	}
	Choix_Capteur(1);
	Prepare_Set_LED(LED_Cible_1);
	Mise_A_Jour_Afficheurs_LED();
	
	//TIMER 1 pour la mise a jour de l'affichage//
	Timer_1234_Init_ff(TIM1, 36000000);
	Active_IT_Debordement_Timer(TIM1,9, CallBackSon);
	
	

//============================================================================	


while	(1)
	{

	}
}

