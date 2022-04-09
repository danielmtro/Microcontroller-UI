#ifndef COMMANDS
#define COMMANDS




//functions to execute changing the seven seg
void sevensegmodule(int number);

//function to turn leds on
void ledOn(void);

//function to turn leds off
void ledOff(void);


void print_help();


//turns the LED on for a fixed number of seconds specified in the argument
void timedLED(int time);


#endif