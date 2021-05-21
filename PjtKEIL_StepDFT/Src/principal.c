

#include "DriverJeuLaser.h"
#include <math.h>
#define pi 3.14159265358979323846

extern int DFT_ModuleAuCarre(short int*, char);
extern short int LeSignal[];
int resultat[64];
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();


	
	

//============================================================================	
	


//int k[6]={17,18,19,20,23,24}; //ca correspond aux frequence de tir des pistolets divises par 5000

for(int k = 0;k<64;k++){
	
	resultat[k] = DFT_ModuleAuCarre(LeSignal, k);
	
}

	
while	(1)
	{

	}
}

