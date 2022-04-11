#include <mc9s12dp256.h>        /* derivative information */

#include "command.h"
#include "serial.h"
#include <string.h>





void sevensegmodule(int number){
  unsigned char SegPat[10] = {
  0x3F,         // pattern for 0
  0x06,         // pattern for 1
  0x5B,         // pattern for 2
  0x4F,         // pattern for 3
  0x66,         // pattern for 4
  0x6D,         // pattern for 5
  0x7D,         // pattern for 6
  0x07,         // pattern for 7
  0x7F,         // pattern for 8
  0x6F          // pattern for 9
  };       
  
  char digit[4] = {
  0xFE,         //enable first seven seg
  0xFD,         //enable second seven seg
  0xFB,         //enable third seven seg
  0xF7          //enable fourth seven seg
  };
 
  PORTB = 0;
  DDRB  = 0xFF;  //enable 7-seg
  DDRP  = 0x3F;  //Select which digit will be used
  PTP   = 0x07;
 
 
  PORTB = 0; //sets 7-seg low
  PTP = 0x07;  //turn the secod 7-seg on
  PORTB = SegPat[number];

  
  
  return;   
}



void ledOn(void)
{
        
  DDRB = 0xFF;
  DDRJ= 0xFF;   // set Port J to Output
  PTJ = 0x00;   // enable LEDs

  PORTB=0xFF;   // All LED on
  DDRP= 0b11111111;
  PTP = 0xFF;
  
  return;
  
}

void ledOff(void) 
{
  DDRB= 0xFF;   // set Port B to output 
  DDRJ= 0xFF;   // set Port J to Output
  PTJ = 0x00;   // enable LEDs

  PORTB=0x00;
  
  return;
  
}


void timedLED(int time) {
  
  int tot = time*1000; //converts time into seconds 
  ledOn();
  delay_ms(tot);
  ledOff();
  
}


void print_help(){
  char* message = "Hello!\nHere are the following commands\n\nType \"L 1\" or \"L 0\" to turn LED on and off\n";
  char* message2 = "Type \"S X\" to change the number on the seven segment display. Note X can be any number from 0-9\n";
  char* message3 = "Type T followed by an integer from 1-9 to turn the LED's on for a set number of seconds.\n";
  char* message4 = "Type W followed by a string to display the string on the terminal.\n\nType \"F\" to exit\n";
  
  SerialOutputString(message, strlen(message));
  SerialOutputString(message2, strlen(message2));
  SerialOutputString(message3, strlen(message3));
  SerialOutputString(message4, strlen(message4));
  
  return;

}

