#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "serial.h"

#define BUFFER 100

//this iterator keeps track of what index in the read_sentence you are up to
volatile int read_index = 0;
char read_sentence[BUFFER];
char write_sentence[BUFFER];

void main(void) {
  /* put your own code here */
  
  
  
	EnableInterrupts;
  
  write_sentence[0] = read_sentence[0];

  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}

//use address 20 for SCI0
//use address 21 for SCI1

interrupt 21 void serialISR() 
{
  
  // Check if data is received. The RDRF flag
  if (SCI1SR1 & 0x20) 
  {
    // End of sentence? Look for a carriage return
    if (SCI1DRL == 0x0D) 
    {    
     read_sentence[read_index] = '\0';
     read_index = 0;
     return;   
    } 
    // Store each character of sentence in buffer
    else
    {
      read_sentence[read_index] = SCI1DRL;
      read_index++;
      
      if(read_index == 100) {
       //execute some error message  
      }
      
      return; 
    }
    
   }
   
}