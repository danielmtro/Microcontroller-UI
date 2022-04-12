#include <mc9s12dp256.h>        /* derivative information */

#include "command.h"
#include "serial.h"
#include <string.h>
#include <stdlib.h>

#define TUNE_SIZE 100
#define NUM_NOTES 31
#define NUM_DURATIONS 7

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

void command_to_tune(char *command, int *notes, int *durations) {
    int i = 0;
    int j = 0;
    int k = 0;
    char user_note[4];
    char user_duration[4];
    char *valid_notes[NUM_NOTES] = {
        "rst",
        "Eb3",
        "E3-",
        "F3-",
        "Gb3",
        "G3-",
        "Ab3",
        "A3-",
        "Bb3",
        "B3-",
        "C4-",
        "Db4",
        "D4-",
        "Eb4",
        "E4-",
        "F4-",
        "Gb4",
        "G4-",
        "Ab4",
        "A4-",
        "Bb4",
        "B4-",
        "C5-",
        "Db5",
        "D5-",
        "Eb5",
        "E5-",
        "F5-",
        "Gb5",
        "G5-",
        "Ab5"
    };
    char *valid_durations[NUM_DURATIONS] = {
        "1-",
        "2-",
        "4-",
        "8-",
        "16",
        "32",
        "64"
    };
    int tune_duration = 0;
    char *error_mssg = "Invalid note given (or placed in wrong position) - command won't execute fully";
    char *playing_mssg1 = "The tune will play for approximately:";
    char *playing_mssg2 = "seconds, at 120 BPM";
    char tune_dur[4];
    while (command[i] != '\0') {
        if (i % 6 == 0) { // command[i] should be a note to play
            strncpy(&user_note[0], &command[i], 3);
            user_note[3] = '\0';
            k = 0;
            while (k < NUM_NOTES) {
                if (!strcmp(user_note, valid_notes[k])) {
                    notes[j] = k; // the index will be used in the play_note function
                    break;
                }
                k++;
            }
            if (k == NUM_NOTES) {
                SerialOutputString(error_mssg, strlen(error_mssg));
                break;
            }
        } else if (i % 6 == 3) { // command[i] should be the duration of the letter
            strncpy(&user_duration[0], &command[i], 2);
            user_duration[2] = '\0';
            k = 0;
            while (k < NUM_DURATIONS) {
                if (!strcmp(user_duration, valid_durations[k])) {
                    durations[j] = k; // the index will be used in the play_note function
                    j++;
                    break;
                }
                k++;
            }
            if (k == NUM_DURATIONS) {
                SerialOutputString(error_mssg, strlen(error_mssg));
                break;
            }
        }
        i++;
    }
    notes[j] = -1;
    durations[j] = -1;

    i = 0;
    while (durations[i] != -1) {
        tune_duration = tune_duration + atoi(valid_durations[durations[i]]);
        i++;
    }
    tune_duration = tune_duration / 8; // semiquavers to seconds
    itoa(tune_duration, tune_dur, 10);
    SerialOutputString(playing_mssg1, strlen(playing_mssg1));
    SerialOutputString(&tune_dur[0], strlen(&tune_dur[0]));
    SerialOutputString(playing_mssg2, strlen(playing_mssg2));
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


