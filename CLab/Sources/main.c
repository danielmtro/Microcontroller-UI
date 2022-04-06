#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <string.h>
#include "string.h"

#define BUFFER 30



interrupt 21 void serialISR();

char sentence[BUFFER];  //takes input 
char command[BUFFER];   //stores the serial input

int j = 0;     //keeps track of the length of command

void main() 
{
  serialRegisters();
  EnableInterrupts;
  
  for(;;);
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
      
      /*
      // Go through all characters in buffer
      for (k = 0; k < j; k++) 
      {
        // Wait for data to be ready
        while(!(SCI1SR1 & 0x80));
        
        // Write to serial
        SCI1DRL = sentence[k];
        
      }
      
      */
      sentence[j] = '\0';
      strcpy(command, sentence);
      SerialOutputString(sentence, j);
      
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