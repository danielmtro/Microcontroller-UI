# Group-7
C-Lab MTRX2700

# Serial interrupts

Part 1 uses a single serial interrupt service routine to read one character at a time for each interrupt (so as to minimise impact on other functions that are running). It also sends out these characters immediately, so that the user can see what they are typing. Then, when the user hits enter, another interrupt is triggered which sends out a whole string.

The serial ports must be first initialised before they can be used - our code is designed in such a way that the initialisation function can be used for any serial port as required. Once initialised, the code will loop through an endless while loop in main. While interrupts allow one character at a time to be read, the flag to move on from exercise 1 is only triggered once the user sends a newline character to finish the string. The main function then moves on to part 2.

# Commands

The command module relies on a flag that indicates whether a new command has been read in, and a second buffer to store the command in (this is so that if a user starts typing a new command while the current one is executing it will not overwrite the current command, however once the user hits enter this will shift the new command and overwrite the old one). Every time the user sends a newline character, the string is moved into the command buffer, the command flag is triggered and the run_instruction function is called. This function acts as a parser for the basic commands, with some error messages for invalid commands or incorrect arguments.

The command module begins by informing the user of the help function (called simply by 'H'), which details the reminaing commands and their arguments. The main then loops endlessly until interrupted with the command. Possible commands are as follows:

H (no arguments) prints all commands

L (0 or 1 as argument) - turns the LEDs on (1) or off (0)

W (some string) - prints out the string to the terminal


S (some number 0-9) - displays the number on a seven segment display

T (some number TODOTODOTODOTODOTODOTODOTODO wasn't sure what the valid numbers were) - turns the LEDs on for the number of seconds specified in the argument, then turns them off again

# Music

M (series of notes and durations) - plays a tune based off the notes and durations. Valid notes are 3 characters (full list in #define section of code), such as C4- or Gb5 for middle C and G flat 2 octaves higher. Valid durations are 2 characters, in powers of 2 (full list in #define section of code), such as 1-, 2- 8-, 16 for semiquaver, quaver, minum, semibrieve.

All the functions above (music and the other basic commands) have some form of error checking to ensure arguments are correct, and print information to the terminal when it is not. The music command is able to run partial instructions if the first part is correct while the second part is not (it will run up until the first invalid syntax). While part of the next song can be queued by starting to write it out, if the user hits enter while the current song is playing it will overwrite the buffer with undefined outcomes - helpful print statements inform the user to wait, as well as how long they should expect to wait, and when they can enter a new command.
