#include <mc9s12dp256.h>        /* derivative information */

#include "command.h"
#include "serial.h"
#include <string.h>

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
    char *string_out = instructions+2;
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
