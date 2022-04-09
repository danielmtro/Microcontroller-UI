#include <mc9s12dp256.h>        /* derivative information */

#include "timing.h"


void delay_ms(unsigned int time){
  int i;
  int j;
    for(i=0;i<time;i++)
      for(j=0;j<4000;j++);
      
  return;
}

