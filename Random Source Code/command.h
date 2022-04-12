#ifndef COMMANDS
#define COMMANDS


//functions to execute changing the seven seg
void sevensegmodule(int number);

//function to turn leds on
void ledOn(void);

//function to turn leds off
void ledOff(void);

//prints the help function
void print_help(void);

// converts the string of notes to arrays that can be passed to the play_song function
void command_to_tune(char *command, int *notes, int *durations);

//turns the LED on for a fixed number of seconds specified in the argument
void timedLED(int time);


#endif