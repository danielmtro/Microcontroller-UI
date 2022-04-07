#include <mc9s12dp256.h>        /* derivative information */

#include "command.h"
#include "serial.h"
#include <string.h>

/*
void run_instruction(char *instruction, int length) {
  char command = instruction[0];
  
  if (command == 'L') {
    char led_arg = instruction[2];
    if (led_arg == '0') {
      led_off();  
    }
    else if (led_arg == '1') {
      led_on();  
    }
    else {
      char *error = "You have tried to use an LED command, but entered an invalid argument. This command accepts the arguments 0 or 1.";
      SerialOutputString(error, strlen(error));
    }
  }
  else if (command =='W') {
    char *string_out = instruction+2;
    SerialOutputString(string_out, strlen(string_out));
  }
  else if (command == 'H') {
    print_help();
  }
  else {
    char *error = "You have entered an invalid command letter. You can enter 'H' for help on valid commands";
    SerialOutputString(error, strlen(error));
  }
  
}

*/

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
 
 
  PORTB = 0; //sets 7-seg low
  PTP = 0x07;  //turn the secod 7-seg on
  PORTB = SegPat[number];

  
  
  return;   
}

