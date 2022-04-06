#include <mc9s12dp256.h>        /* derivative information */

#include "serial.h"

#define BUFFER 100


// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
SerialPort SCI0 = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};


//initialises the serial registers



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




void SerialOutputString(char* string,int length){

  int k = 0;
  
  for (k = 0; k < length; k++) 
      {
        // Wait for data to be ready
        while(!(SCI1SR1 & 0x80));
        
        // Write to serial
        SCI1DRL = string[k];
        
      }
  
  // Wait for data to be ready
  while(!(SCI1SR1 & 0x80));
        
  // Write to serial
  SCI1DRL = 0x0D;
  return; 
}



void clear_string(char* string) {
  int i;

  for(i = 0; i < BUFFER; i++) {
   string[i] = '\0'; 
  }
  
  return; 
}
