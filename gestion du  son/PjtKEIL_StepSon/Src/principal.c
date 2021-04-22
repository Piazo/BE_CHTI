#include "DriverJeuLaser.h"
#include "GestionSon.h"


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

Timer_1234_Init_ff(TIM4,6552);
Timer_1234_Init_ff(TIM1,6552*10000);
//config de la pwm
PWM_Init_ff(TIM3, 3, 720);

//debordement prio 2 sur la fct callbackson
Active_IT_Debordement_Timer(TIM4, 2, CallBackSon);
Active_IT_Debordement_Timer(TIM1, 1, StartSon);

//liaison du canal 3 a la pin PB.0
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	

//============================================================================	
	
	
while	(1)
	{
	}
}

