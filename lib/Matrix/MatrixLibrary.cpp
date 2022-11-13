/*---------------DATASHEET----------------------
  https://www.farnell.com/datasheets/1793938.pdf
-----------------------------------------------*/

#include <Arduino.h>
#include <Wire.h>
#include <MatrixLibrary.h>

const byte AGD2188_ADDRESS_DEFAULT = 0x70; 
byte matrix_address;
const byte NOW = 0x01;
// 0x71 remember that 0x just neans its a hex number and the two following digits are the actual hex 71 = 1110001
// in the datasheet figure 33, this matches the A0-A2 address bytes

// Lay out the constants for reading back the switch states
const byte X0 = 0x34;
const byte X1 = 0x3C;
const byte X2 = 0x74;
const byte X3 = 0x7C;
const byte X4 = 0x35;
const byte X5 = 0x3D;
const byte X6 = 0x75;
const byte X7 = 0x7D;

const byte X_ADDRESS_FOR_READING[] = {X0,X1,X2,X3,X4,X5,X6,X7};
//Making the first bit to tell to turn off or on connection
const byte ON_BIT = 0b1;
const byte OFF_BIT = 0b0;

// //Settign up x address for converting to BYTE
const byte W_X0 = 0b0000;
const byte W_X1 = 0b0001;
const byte W_X2 = 0b0010;
const byte W_X3 = 0b0011;
const byte W_X4 = 0b0100;
const byte W_X5 = 0b0101;
const byte W_X6 = 0b1000;
const byte W_X7 = 0b1001;

const byte x_byte_array[8] = {W_X0,W_X1,W_X2,W_X3,W_X4,W_X5,W_X6,W_X7};

// //Setting up y address for converting to BYTE
const byte W_Y0 = 0b000;
const byte W_Y1 = 0b001;
const byte W_Y2 = 0b010;
const byte W_Y3 = 0b011;
const byte W_Y4 = 0b100;
const byte W_Y5 = 0b101;
const byte W_Y6 = 0b110;
const byte W_Y7 = 0b111;

const byte y_byte_array[8]= {W_Y0,W_Y1,W_Y2,W_Y3,W_Y4,W_Y5,W_Y6,W_Y7};

//----------------------------- Constructors-------------------------------
AGD2188::AGD2188()
{
  matrix_address  = AGD2188_ADDRESS_DEFAULT;
  Wire.begin(); // join i2c bus (address optional for master) multiple Wire.begins are fine
}

// Overloaded constructor for addressing multiple chips //
AGD2188::AGD2188(byte address)
{
  if(address <0x70 || address > 0x77){
    //Serial.println("ERROR: only 70-77 are valid AGD2188 addresses");
  } else {
    matrix_address = address;
    //Serial.print("Matrix initiated at: ");
    //Serial.println( matrix_address, HEX);
  }
  Wire.begin(); 
}
//--------------------------------------------------------------------------

  byte convert_to_byte(bool OnOrOff, int x, int y){
    byte x_byte = x_byte_array[x];
    byte y_byte = y_byte_array[y];
    byte OnOrOff_byte = 0b0;

    if(OnOrOff){
        OnOrOff_byte = ON_BIT;
    } else {
        OnOrOff_byte = OFF_BIT;
    }
    byte write_converted = OnOrOff_byte << 7 | x_byte << 3 | y_byte;
    return write_converted;
}

void AGD2188::readData(int x){ 
  //const byte read_byte = 0xE3; // writeData(x_address);   this needs the initial byte to be in READ MODE, then it needs the alternate X code as in Table 8.
  byte data_array[2];
  data_array[0] = X_ADDRESS_FOR_READING[x-1];//x_byte_array[x-1]; 
  data_array[1] = NOW;
  Wire.beginTransmission(matrix_address);
  Wire.write(data_array,2);
  Wire.endTransmission();
  Wire.requestFrom(matrix_address, 2); 
  while(Wire.available())
  {
    /*
    This Returns a byte where each bit represents the state of the given x's connection to 
    the position in the byte's y
    EXAMPLE: given x 3
    returned byte 10001001
    means that x3 is connected to y 0,4 and 7
    */
    String message =  String(x) + "connected to: ";
    Serial.print(message);
    Serial.println(Wire.read(), BIN); 
  }
  Serial.println();  
}


 void AGD2188::writeData(bool OnOrOff, int x, int y){ 
  String message = "x: " + String(x) + " connected to y: " +  String(y);
  Serial.print(message);
  byte data_input = convert_to_byte(OnOrOff,x,y);
  byte data_array[2];  
  data_array[0] = data_input; //on off is 1st bit, next 4 is x adress last three is the y address
  data_array[1] = NOW;  
  Wire.beginTransmission(matrix_address); 
  Wire.write(data_array, 2);
  Wire.endTransmission();    
}


void AGD2188::wipeChip()
{
  unsigned long preTime = millis();
  // These FOR loops will cycle from X0 - Y0 to X7 - Y7
  // The "x_value" is derived from Table 7 (AX3-AX0).  Note that it's not contiguous because they reserve
  // values for the read register values (seen above).  
  // The "y_value" is contiguous, with 0b000 corresonding to Y0 and 0b111 corresponding to Y7

  // This loop pair will ensure everything is initialized to NOT CONNECTED the very first time it runs.
  // It will look like a whole bunch of nothing is happening on the Serial port.
  //this take on average 22 millsecs without printing to serial.
  //Alternative is to pull "reset" pin HIGH which should wipe the chip in about 200 nano sec.

 for(int y = 0; y < 8; y++){  
    int y_value = y;
    for(int x = 0; x < 8; x += 1){  
      int x_value = x;      
      writeData(false,x_value,y_value);
    }
  }
  String m_chip_wiped = " Chip wiped(ms):  ";
  String output_message = m_chip_wiped + (millis()-preTime); //this take on average 9 millsecs without printing to serial.
  Serial.println(matrix_address + output_message);
}


void AGD2188::writeArray(int input_array[8], int sizeOfArray){
  //Step 0.5 CHECK IF ALL ZEROS
  wipeChip();
  // this check if all are zero in which case connect input to output
  bool should_pass = true;
  for(int i = 0; i < sizeOfArray; i++){
    if(input_array[i]!=0){
      should_pass = false;
    }
  }
  if(should_pass){
    writeData(true,7,7);
    return;
  }

  // step One: find lowest number in array.
  int minVal = 7;
  for (int i = 0; i < sizeOfArray; i++){
    if(input_array[i] !=0 && input_array[i] < minVal){
      minVal = input_array[i];
    }
  }

  //Step Two: Assign input device to each of the positions with minVal;
  for (int i = 0; i < sizeOfArray; i++){
      if(input_array[i]==minVal){
         writeData(true,7,i);
       }
  }

  //Step Three: iterate through and check for next value 
  int preVal = minVal;
  int curVal = minVal;

   for (int i = 0; i < sizeOfArray; i++){
    // 3.0 finds the next highest number in the array
    int interval = 1;
    for(int p = 0; p < sizeOfArray; p++){
      if(input_array[p]==(preVal+interval)){
        curVal = preVal+interval;
      }
      if(curVal == preVal && p == 7){
        interval ++;
        if(interval <6){
          p=-1;
        }
      }
    }
    // 3.5 This connects all of the currently highest values to all of the previous highest values
    if(curVal!=preVal){
     for(int o = 0; o < sizeOfArray; o++){
      if(input_array[o]==curVal){
        for(int l = 0; l<sizeOfArray; l++){
          if(input_array[l]==preVal){
          writeData(true,l,o);
          }
        }
      }
    }
    preVal = curVal;
    }
   }
   // Step 4: Connect highest values to output
   for(int m = 0; m <sizeOfArray; m++){
    if(input_array[m]==curVal){
      writeData(true,m,7);
    }
  }
} 
//////////////////////////////////////////////////////////////

void AGD2188::testChip(){
 for (int i =0; i<8; i++){
    for (int j =0; j<8; j++){
      writeData(true,i,j);
      delay(50);
    }
    readData(i);
  }
  wipeChip();
}
