#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <string.h>
#include <stdlib.h>
#include "serial.h"
#include "command.h"
#include "timing.h"

#define BUFFER 30

#define rest 20
#define Eb3 9641
#define E3  9100
#define F3  8589
#define Gb3 8107
#define G3  7652
#define Ab3 7223
#define A3  6817
#define Bb3 6434
#define B3  6073
#define C4  5733
#define Db4 5411
#define D4  5107
#define Eb4 4820
#define E4  4550
#define F4  4294
#define Gb4 4053
#define G4  3826
#define Ab4 3611
#define A4  3408
#define Bb4 3611
#define B4  3036
#define C5  2866
#define Db5 2705
#define D5  2553
#define Eb5 2410
#define E5  2275
#define F5  2147
#define Gb5 2026
#define G5  1913
#define Ab5 1805
#define A5  1704


#define longnote  128      
#define dbreve    64
#define breve     32
#define semibreve 16
#define minim     8
#define crotchet  4
#define quaver    2
#define semiquav  1


                                    //index's 
                                    
unsigned int note[] = {rest,        //0
    Eb3,                            //1
    E3,                             //2
    F3,                             //3
    Gb3,                            //4
    G3,                             //5
    Ab3,                            //6
    A3,                             //7
    Bb3,                            //8
    B3,                             //9
    C4,                             //10
    Db4,                            //11
    D4,                             //12
    Eb4,                            //13
    E4,                             //14
    F4,                             //15
    Gb4,                            //16
    G4,                             //17
    Ab4,                            //18
    A4,                             //19
    Bb4,                            //20
    B4,                             //21
    C5,                             //22
    Db5,                            //23
    D5,                             //24
    Eb5,                            //25
    E5,                             //26
    F5,                             //27
    Gb5,                            //28
    G5,                             //29
    Ab5                             //30
    };

                                                
int mii_song_notes[] = {16, 19, 23, 19, 16, 12, 0, 12, 0, 12, 0, 16, 19, 23, 0, 19, 16, 26, 25, 24};  //20
int mii_song_duration[] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 6, 6, 6, 7, 6, 6, 5, 6, 6};

//most songs play at 120 bpm
//2 beats per second

//usually a crotchet is 1 beat but in this case it is 4. Consider each duration unit to be
//0.125 seconds

unsigned int duration[] =
{
    longnote,
    dbreve,
    breve,
    semibreve,
    minim,
    crotchet, 
    quaver,
    semiquav
};


//functions here
interrupt 21 void serialISR();
interrupt 13 void speakerISR();
void run_instruction(char *instruction);
void death_to_hcs12();
void play_note(int note_num, int duration_num);
void play_mii();

//variable for the period of the note being played
volatile int period = 1000000;


//global variables involved in interrupt sequence


char sentence[BUFFER];  //takes input 
char command[BUFFER];   //stores the serial input


int j = 0;     //keeps track of the length of command
int exercise_1_flag = 0;

//new command is zero if there is a new command that hasn't been read
//if the command has been read it will be zero
int new_command = 0;

void main() 
{
  int number;
  
  
  //strings to be used in program
  char* completed_1 = "Exercise 1 completed!";
  char* welcome_message = "\nHello!\nTo proceed, please enter a command. If you don't know the current commands type 'H'.\nEnjoy!";
   
  
   // Disable all interrupts
	DisableInterrupts;
	
	//enable serial input and output
	serialRegisters();
	
	
	//setup timer for prescaler of 8, output compare on TC5 and toggling of speaker. NO interrupts enabled.
	setup_timers();
	
	
  EnableInterrupts;
  
  
  
  //exercise 1 demonstration
  while(exercise_1_flag == 0){
  }
  
  SerialOutputString(completed_1, strlen(completed_1));
  
  
  
  //testing speaker function
  play_mii();
  
  
  //Exercise 2 demonstration
  SerialOutputString(welcome_message, strlen(welcome_message));
  
  //enable everything
  
  
  new_command = 0;
  
  
  
  while(command[0] != 'F'){
    
    while(new_command == 0);
    
    //a little easter egg
    if(strcmp(command, "kill yourself") == 0){
      death_to_hcs12();
      
      continue;
    }
    
    //runs the instruction that is parsed
    run_instruction(command);
    
  }
   
  
  while(command[0] != 'F'){
    
    if(new_command == 1 ) {
      number = atoi(command);
      sevensegmodule(number);
      new_command = 0;
    }
  }
 
  //test leds
  //ledOn();
  
  
 
  
  //poll command char
  
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
      //add in null terminator to string    
      sentence[j] = '\0';
      
      //copies sentence to command 
      strcpy(command, sentence);
      
      //sets command to 1 to make sure program knows there is a new command that hasn't been read
      new_command = 1;
     
      
      //output the newline to terminal
      SerialOutputChar(0x0D);
      
      // Reset buffer
      j = 0;
      
      //set flag to know that exercise 1 is complete
      exercise_1_flag = 1;
      
    } 
    
    // Store each character of sentence in buffer
    else
    {
      sentence[j] = SCI1DRL;
      SerialOutputChar(sentence[j]);
      
      //incrememnt length of word
      j = j + 1;
      
      //buffer overflow condition
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

interrupt 13 void speakerISR() {

  TC5 = TC5 + period;

}


void run_instruction(char *instruction) {
  char command = instruction[0];
  char *error = "You have tried to use an LED command, but entered an invalid argument. This command accepts the arguments 0 or 1.";
  char *string_out;  
  char *error2 = "You have entered an invalid command. You can type 'H' for help on valid commands";
  char *error_sseg = "You have tried to use an Seven Seg command, but entered an invalid argument. This command accepts the arguments integers 0-9.";
  char *error_time = "You have tried to use a LED timed command but entered an invalid argument.This command accepts the arguments integers 0-9.";
  int sseg_arg;
  char *nums = "0123456789";
  int i;
  
  
  if (command == 'L') {                                        // Handling for the LED functions
    char led_arg = instruction[2];
    if (led_arg == '0') {
      ledOff();  
    }
    else if (led_arg == '1') {
      ledOn();  
    }
    else {
      SerialOutputString(error, strlen(error));
    }
  }
  else if (command =='W') {                                    //Handling for writing an output
    string_out = instruction+2;
    SerialOutputString(string_out, strlen(string_out));
  }
  else if (command == 'H') {                                  //Handling for help function
    print_help();
  }
  else if (command == 'S'){                                  //Handling for 7-seg function
  
    for(i = 0; i < 10; i++){
      if(instruction[2] == nums[i]){
        sseg_arg = i;
      }
      
    }
    
    
    if(sseg_arg >= 0) {
      if(sseg_arg <= 9){ 
         sevensegmodule(sseg_arg);
      }else{
    
       SerialOutputString(error_sseg, strlen(error_sseg));
      
    } 
    } else{
    
       SerialOutputString(error_sseg, strlen(error_sseg));
      
    }
  } else if (command == 'F'){                           //Exit command
       ledOff();
       SerialOutputString("exiting...", 10);
  } else if (command == 'T'){                           //Handling for timed LED command
    
    sseg_arg = -1;
    for(i = 0; i < 10; i++){
      if(instruction[2] == nums[i]){         //use the seven seg arg for this as well cos im lazy
        sseg_arg = i;
      }
    }
    
    if(sseg_arg == -1){
      
      SerialOutputString(error_time, strlen(error_time));
    } else{
    
      timedLED(sseg_arg);
    }
      
  }
  else {   
    SerialOutputString(error2, strlen(error2));
  }
  
  new_command = 0;
  
}




//this function plays a note based on two inputs
//1st input: index of note in note array defined above
//2nd input: index of duration in duration array defined above.

//no outputs - just plays the note for the desired duration
void play_note(int note_num, int duration_num) {
  
  int time = duration[duration_num]*125;
  period = note[note_num];
  
  //toggle on successful output compare
	TCTL1 = 0x04;
  
  //enable timer interrupts
  TIE = 0x20;
  
  //set first output compare to happen 
	TC5 = TCNT + period;
  
  //wait the duration of the note
  delay_ms(time);
  
  //set to low
  TCTL1 = 0x00;
  
  //disable timer interrupts (stop the speaker from playing anything else)
  TIE = 0x00;
  
}


void play_mii() {
int i;


for(i = 0; i < 20; i++) {
  
  play_note(mii_song_notes[i], mii_song_duration[i]);
    
}
return;

}


//a little easter egg
void death_to_hcs12(){
  
  int i;
  new_command = 0;
  
  for(i = 0; i < 100; i++){
    SerialOutputString("fuck you",8);                                
  }
  
  SerialOutputString("Please enter a command", 22);
  
}


