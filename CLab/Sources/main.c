#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <string.h>


#define BUFFER 10


void serialRegisters(void);
interrupt 21 void serialISR();

char sentence[BUFFER];
int j = 0;

void main() 
{
  serialRegisters();
  EnableInterrupts;
  
  for(;;);
}

void serialRegisters(void) 
{
  // Set baud rate to 9600
  SCI1BDL = 0x9C;
  SCI1BDH = 0;
  
  // No fancy stuff needed
  SCI1CR1 = 0;
  
  // 2C = 0010110, Enable receive interrupt, transmit, receive
  SCI1CR2 = 0x2C;
}

interrupt 21 void serialISR() 
{
  int i = 0;
  int k = 0;
  
  char* error_sentence = "You've exceeded the buffer limit. Try again!\n";
  int length = strlen(error_sentence);
  
  // Check if data is received. The RDRF flag
  if (SCI1SR1 & 0x20) 
  {
    // End of sentence? Look for a carriage return
    if (SCI1DRL == 0x0D) 
    {
      // Don't do anything unless you are ready to send data. The TDRE flag
      // May not need this line since I do it again below
      while(!(SCI1SR1 & 0x80));
      
      // Go through all characters in buffer
      for (k = 0; k < j; k++) 
      {
        // Wait for data to be ready
        while(!(SCI1SR1 & 0x80));
        
        // Write to serial
        SCI1DRL = sentence[k];
        
      }
      
      while(!(SCI1SR1 & 0x80));
        
       // Write to serial
       SCI1DRL = 0x0D;
      
      // Reset buffer
      j = 0;
    } 
    
    // Store each character of sentence in buffer
    else
    {
      sentence[j] = SCI1DRL;
      j = j + 1;
      
      if(j == BUFFER) {
      
         for (i = 0; i < length; i++) 
        {
          // Wait for data to be ready
          while(!(SCI1SR1 & 0x80));
          
          // Write to serial
          SCI1DRL = error_sentence[i];
          
        }
      
       j = 0; //Reset buffer
        
      }
    }
  }
}