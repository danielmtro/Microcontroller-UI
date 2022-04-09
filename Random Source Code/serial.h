#ifndef SCI1_HEADER
#define SCI1_HEADER


// NOTE: these are stored as pointers because they 
//       are const values so we can't store them directly
//       in the struct
typedef struct SerialPort {
  byte *BaudHigh;
  byte *BaudLow;
  byte *ControlRegister1;
  byte *ControlRegister2;
  byte *DataRegister;
  byte *StatusRegister;
} SerialPort;


// make two instances of the serial port (they are extern because
//   they are fixed values)
extern SerialPort SCI0, SCI1;

//sets up the serial registers
void serialRegisters(void);


//takes a letter input and prints it to the terminal
void SerialOutputChar(char letter);


//takes as an input a string and its lenghth.
//Prints the string to the terminal
void SerialOutputString(char* string,int length);
 

//set all the values in a string to a null value
void clear_string(char* string);

 
#endif