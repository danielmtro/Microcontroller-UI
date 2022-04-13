# Group-7
C-Lab MTRX2700

Contributions:

Will:

- Documentation
- Command parser for part 2
- Command parser for part 3
- Play song function for part 3

Daniel:
- Serial interrupt (read and write) for part 1
- Delay function
- Split seven segment function for part 2 with Henry
- Timed LED function for part 2
- Output compare for part 3

Henry:
- LED on and off functions for part 2
- Split seven segment function for part 2 with Daniel
- Test cases

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

T (some number 1-9) - turns the LEDs on for the number of seconds specified in the argument, then turns them off again

# Music

M (series of notes and durations) - plays a tune based off the notes and durations. Valid notes are 3 characters (full list in #define section of code), such as C4- or Gb5 for middle C and G flat 2 octaves higher. Valid durations are 2 characters, in powers of 2 (full list in #define section of code), such as 1-, 2- 8-, 16 for semiquaver, quaver, minum, semibrieve.

All the functions above (music and the other basic commands) have some form of error checking to ensure arguments are correct, and print information to the terminal when it is not. The music command is able to run partial instructions if the first part is correct while the second part is not (it will run up until the first invalid syntax).

Once the user is finished with entering their own tunes, they can enter the final command 'F' (they will not be able to enter any more commands after this), and be treated to a playing of the mii theme before the microcontroller just loops endlessly. The user will still be able to type (and see what they are typing), it will just have no effect on the controller.

# Test cases

###Exercise 1

>input = "hello/n"
>
>output (terminal) = "hello\n"
>
>output (terminal) = "Exercise 1 completed!\n"
>
>output (terminal) = "\nHello!\nTo proceed, please enter a command. If you don't know the current commands type 'H'.\nEnjoy!"
>
>
>note: as input is typed each character will be displayed to terminal before the return carage is used. i.e you can see what youre typing before pressing >enter




>input = "fjhjkcfhdwkwkjekdejwklcje2cle2jckewjcklewjckecklneklcnekncehckle3hfkld\n"
>
>output = "You've exceeded the buffer limit. Try again!\n"
>
>note: This error will allow you to re-enter an input less than 100 characters 




###Exercise 2


>input = "Jwdwj/n"
>
>output (terminal) = "You have entered an invalid command. You can type 'H' for help on valid commands"



>input = "H/n"
>
>output (terminal) =  "Hello!
>
>                      Here are the following commands
>                      
>                      Type "L 1" or "L 0" to turn LED on and off
>                      
>                      Type "S X" to change the number on the seven segment display. Note X can be any number from 0-9
>                      
>                      Type "T" followed by an integer from 1-9 to turn the LED's on for a set number of seconds.
>                      
>                      Type "W" followed by a string to display the string on the terminal.
>                      
>                      Type "F" to exit/n"
                      


>input = "L 4/n"
>
>output (terminal) = "Command in progress/n"
>
>output (terminal) = "You have tried to use an LED command, but entered an invalid argument. This command accepts the arguments 0 or 1."
>
>output (LEDs) = remain in current state




>input = "L 1/n"
>
>output (terminal) = "Command in progress/n"
>
>output (LEDs) = All on (regardless of previous state of LEDs)
>
>output (terminal) = "Command finished, Please enter new command/n"



>input = "L 0/n"
>
>output (terminal) = "Command in progress/n"
>
>output (LEDs) = All off (regardless of previous state of LEDs)
>
>output (terminal) = "Command finished, Please enter new command/n"



>input = "T 8/n"
>
>output (terminal) = "Command in progress/n"
>
>output (LEDs) = All on for 8 seconds, then off 
>
>output (terminal) = "Command finished, Please enter new command/n"



>input = "T 8/n" 
>
>output (terminal) = "Command in progress/n"



>input = "T 5/n"
>
>output (LEDs) = All on for 8 seconds, then off
>
>
>note: second input is read but not acted on as new_command flag is not triggered untill first process is completed



>input = "T 20/n"
>
>output (terminal) = "You have tried to use a LED timed command but entered an invalid argument.This command accepts the arguments integers 0-9."



>input = "S 5/n"
>
>output (terminal) = "Command in progress/n"
>
>output (7-SEG) = 5
>
>output (terminal) = "Command finished, Please enter new command/n"



>input = "S 4/n"
>
>output (terminal) = "Command in progress/n"
>
>input = "S 7/n"
>
>output (7-SEG) = 4
>
>output (terminal) = "Command finished, Please enter new command/n"



>input = "S E"
>
>output (terminal)= "You have tried to use an Seven Seg command, but entered an invalid argument. This command accepts the arguments integers 0-9."


>input = "S 23/n"
>
>output (7-SEG) = 2
>
>
>note: just displays first digit



>input = "W Hello world!/n"
>
>output (terminal) = "Command in progress/n"
>
>output (terminal) = "Hello world!/n"
>
>output (terminal) = "Command finished, Please enter new command/n"



>input = "W Hello world!/n"
>
>output (terminal) = "Command in progress/n"
>
>input = "W Goodbye world:(/n"
>
>output (terminal) = "Hello world!/n"
>
>output (terminal) = "Command finished, Please enter new command/n"


>input = "M C5-8-/n"
>
>output (terminal) = "Command in progress/n"
>
>output (terminal) = "this tune will play for aprox: 
>
>                     1
>                     
>                     seconds, at 120BPM
>                    
>                     
>output (speaker) =  will play c (one octave above middle c) for one minim


>input = "M C5-8- H7-9-/n"
>
>output (terminal) = "Command in progress/n"
>
>output (terminal) = "Invalid note given (or placed in wrong position) - command wont execute fully/n"
>
>output (terminal) = "this tune will play for aprox: 
>
>                     1
>
>                     seconds, at 120BPM
>                     
>output (speaker) =  will play c (one octave above middle c) for one minim
>
>output (terminal) = "Command finished, Please enter new command/n"













