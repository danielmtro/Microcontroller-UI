#include <mc9s12dp256.h>        /* derivative information */

#include "timing.h"


void delay_ms(unsigned int time){
  int i;
  int j;
    for(i=0;i<time;i++)
      for(j=0;j<4000;j++);
}

//
// TCNT max value is 65.536
//
// So 1 cyle is equal to 65.536 / 24mHz 
//
// 1 cyle = 65.536/24.000.000 = 2.73 ms
//

// Timer Counter to 1 sn
// 1s delay implemented by using Timer Overflow Property of Timer Module.

void delay_1sn(void) 
{

 int i;
 
 TSCR1 = 0x80;                            // Enable Timer
 TSCR2 = 0x00;                            // No interrupt, No Prescale
                                          // Count Value
 for(i=0; i<366; ++i) {                  
  TFLG2 = 0x80;                           // Clear TOF
  while(!(TFLG2 & TFLG2_TOF_MASK));       // Wait for overflow flag to be raised 
 }