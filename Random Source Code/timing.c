#include <mc9s12dp256.h>        /* derivative information */

#include "timing.h"


void delay_ms(unsigned int time){
  int i;
  int j;
    for(i=0;i<time;i++)
      for(j=0;j<4000;j++);
      
  return;
}


void setup_timers(){
  
  // Enable timer and fast flag clear
	TSCR1 = 0x90;
	
	// Set prescaler to 8
	TSCR2 = 0x03;
	
	//TSCR2 = 0b00000111;
	
	//enable output compare on pin 5
	TIOS = 0x20;
	
	return;
}
