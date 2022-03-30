#include <mc9s12dp256.h>        /* derivative information */

#include "serial.h"


// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort SCI1 = {&SCI1BDH, &SCI1BDL, &SCI1CR1, &SCI1CR2, &SCI1DRL, &SCI1SR1};
SerialPort SCI0 = {&SCI0BDH, &SCI0BDL, &SCI0CR1, &SCI0CR2, &SCI0DRL, &SCI0SR1};



// InitialiseSerial - Initialise the serial port SCI1
// Input: baudRate is tha baud rate in bits/sec
void SerialInitialise(int baudRate, SerialPort *serial_port) {
  
  // Baud rate calculation from datasheet
  switch(baudRate){
	case BAUD_9600:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=156;
	  break;
	case BAUD_19200:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=78;
	  break;
	case BAUD_38400:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=39;
	  break;
	case BAUD_57600:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=26;
	  break;
	case BAUD_115200:
      *(serial_port->BaudHigh)=0;
      *(serial_port->BaudLow)=13;
	  break;
  }
  
  *(serial_port->ControlRegister2) = SCI1CR2_RE_MASK | SCI1CR2_TE_MASK;
  *(serial_port->ControlRegister1) = 0x00;
}
    
        
void SerialOutputChar(char data, SerialPort *serial_port) {  
  while((*(serial_port->StatusRegister) & SCI1SR1_TDRE_MASK) == 0){
  }
  
  *(serial_port->DataRegister) = data;
}



void SerialOutputString(char *pt, SerialPort *serial_port) {
  while(*pt) {
    SerialOutputChar(*pt, serial_port);
    pt++;
  }            
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
     return   
    } 
    // Store each character of sentence in buffer
    else
    {
      read_sentence[read_index] = SCI1DRL;
      read_index++;
      
      if(read_index == 100) {
       //execute some error message  
      }
      
      return 
    }
    
   }
   
}

void clear_string(char* string) {

  for(int i = 0; i < BUFFER; i++) {
   string[i] = '\0'; 
  }
  
  return 
}
