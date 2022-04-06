#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <string.h>
#include "serial.h"

#define BUFFER 30



interrupt 21 void serialISR();


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
  
  char* completed_1 = "Exercise 1 completed!";
  char* welcome_message = "\nHello!\nTo proceed, please enter a command. If you don't know the current commands type 'H'.\nEnjoy!";
  
  
  serialRegisters();
  EnableInterrupts;
  
  
  //exercise 1 demonstration
  while(exercise_1_flag == 0){
  }
  
  SerialOutputString(completed_1, strlen(completed_1));
  
  
  
  //Exercise 2 demonstration
  SerialOutputString(welcome_message, strlen(welcome_message)); 
  
  
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
      
    
      sentence[j] = '\0';
      
      //copies sentence to command 
      strcpy(command, sentence);
      
      //sets command to 1 to make sure program knows there is a new command that hasn't been read
      new_command = 1;
      
      SerialOutputChar(0x0D);
      
      // Reset buffer
      j = 0;
      
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