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


void serialRegisters(void);

void SerialOutputString(char* string,int length);
 

//set all the values in a string to a null value
void clear_string(char* string);
 
#endif