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
 
  PORTB = 0x00; //sets 7-seg low
  PTP = 0x07;   //turn the secod 7-seg on
  PORTB = num_to_disp(number);
  return;   
}

int num_to_disp(int number){

  switch(number){
    
    case 0:
      return 0x3F;
      break;
    
    case 1:
      return 0x06;
      break;
     
    case 2:
      return 0x5B;
      break;
    
    case 3:
      return 0x4F;
      break;
    
    case 4:
      return 0x66;
      break;
    
    case 5:
      return 0x6D;
      break;
      
    case 6:
      return 0x7D;
      break;
     
    case 7:
      return 0x07;
      break;
    
    case 8:
      return 0x7F;
      break;
    
    case 9:
      return 0x6F;
      break;      
  }
  
}