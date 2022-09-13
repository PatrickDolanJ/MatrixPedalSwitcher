
// https://www.farnell.com/datasheets/1793938.pdf
#include <Arduino.h>
#include <Wire.h>
#include <MatrixLibrary.h>

byte AGD2188_ADDRESS_DEFAULT = 0b1110;
byte AGD2188_ADDRESS = 0x71;  //Arduino uses 7 bit addresses. this probably means that arduino 
//only has 128 possible adress that it can write to. you probably have to drop the least signifigant bit 
//which we guess means we drop the highest bit meaning the one all the way to the left. If you have 
//an 8 bit address, drop the LSB and shift right
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
//Making the first bit to tell to turn off or on connection
const byte ON_BIT = 0b1;
const byte OFF_BIT = 0b0;
//////////////////////////

// 0-7 address bits(3) These are determined by the state of the three
// address pins on the chip                            
const byte ADDRESS_0 = 0b000;
const byte ADDRESS_1 = 0b001;
const byte ADDRESS_2 = 0b010;
const byte ADDRESS_3 = 0b011;
const byte ADDRESS_4 = 0b100;
const byte ADDRESS_5 = 0b101;
const byte ADDRESS_6 = 0b110;
const byte ADDRESS_7 = 0b111;

const byte ADDRESS_BITS[8] = {ADDRESS_0,ADDRESS_1,ADDRESS_2,ADDRESS_3,ADDRESS_4,ADDRESS_5, ADDRESS_6,ADDRESS_7};
////////////////////////////////


// //Settign up x array for converting to BYTE
const byte W_X0 = 0b0000;
const byte W_X1 = 0b0001;
const byte W_X2 = 0b0010;
const byte W_X3 = 0b0011;
const byte W_X4 = 0b0100;
const byte W_X5 = 0b0101;
const byte W_X6 = 0b1000;
const byte W_X7 = 0b0001;

const byte x_byte_array[8] = {W_X0,W_X1,W_X2,W_X3,W_X4,W_X5,W_X6,W_X7};
/////////////////

// //Setting up y adress for converting to BYTE
const byte W_Y0 = 0b000;
const byte W_Y1 = 0b001;
const byte W_Y2 = 0b010;
const byte W_Y3 = 0b011;
const byte W_Y4 = 0b100;
const byte W_Y5 = 0b101;
const byte W_Y6 = 0b110;
const byte W_Y7 = 0b111;

const byte y_byte_array[8]= {W_Y0,W_Y1,W_Y2,W_Y3,W_Y4,W_Y5,W_Y6,W_Y7};

/////////////////// Constructors //////////////////////
AGD2188::AGD2188()
{
  Wire.begin(); // join i2c bus (address optional for master) this may not be good to do inside a library, may be better handled by dependecy injection or just let main handle it.
}


// Overloaded constructor for addressing multiple chips //
AGD2188::AGD2188(int address)
{
  if(address <0 || address > 7){
    Serial.println("ERROR: only 0-7 are valid AGD2188 addresses");
  } else {



  }
  Wire.begin(); 
}
/////////////////////////////////////////////////////

  byte AGD2188::convert_to_byte(bool OnOrOff, int x, int y){
    byte x_byte = x_byte_array[x];
    byte y_byte = y_byte_array[y];
    byte OnOrOff_byte = 0b0;

    if(OnOrOff){
        OnOrOff_byte = ON_BIT;
    } else {
        OnOrOff_byte = OFF_BIT;
    }
    byte write_converted = OnOrOff_byte << 7 | x_byte << 3 | y_byte;
    Serial.print("BIN value: ");
    Serial.println(write_converted, BIN);
    return write_converted;
}

void AGD2188::read_data(int x){ 
  //const byte read_byte = 0xE3; // write_data(x_address);   this needs the initial byte to be in READ MODE, then it needs the alternate X code as in Table 8.
  //This is as the person on the arduino forums has it, but im not sure this will actually work...
  byte data_array[2];
  data_array[0] = x_byte_array[x-1]; 
  data_array[1] = NOW;
  Wire.beginTransmission(AGD2188_ADDRESS);
  Wire.write(data_array,2);
  Wire.endTransmission();
  Wire.requestFrom(AGD2188_ADDRESS, 2); //2nd arguement is probably expecting 2 bytes back 
  while(Wire.available())//this probably functions likea stream. meaning its says while there is data on the next line, do this loop
  {
    Serial.println(Wire.read(), BIN);// this probably spits out a byte at a time
  }
  Serial.println();  
}


 void AGD2188::write_data(bool OnOrOff, int x, int y){ //void write_date(int x, int y)
   byte data_input = convert_to_byte(OnOrOff,x,y);
   byte data_array[2]; //passing in to this fuction the data we want to write 
   data_array[0] = data_input; //on off is 1st bit, nw=ext 4 is x adress last three is the y address
   data_array[1] = NOW;  // Hardcoded 2nd byte to NOW.  See comment below about DON'T CARE for read address setup.
   Wire.beginTransmission(AGD2188_ADDRESS); // transmit to device
   Wire.write(data_array, 2);
   Wire.endTransmission();    // stop transmitting
   String m_message;
   if (OnOrOff){
    m_message = "Connected: ";
   } else {
    m_message = "Disconnected: ";
   }
  m_message += x;
  m_message += " to ";
  m_message += y;
  Serial.println(m_message);
}

// To execute a read, you first have to WRITE the address value to the device.
// The second byte of the write is DON'T CARE, but it is necessary.  So we leave it as the "NOW" byte.
// After you setup the read address, all you have to do is request 2 bytes.  The first byte is always all "0".
// (See bottom trace in Figure 35)

void AGD2188::wipe_chip()
{
  delay(1000);
  Serial.println(millis());
  // These FOR loops will cycle from X0 - Y0 to X7 - Y7
  // The "x_value" is derived from Table 7 (AX3-AX0).  Note that it's not contiguous because they reserve
  // values for the read register values (seen above).  Kind of a pain.
  // The "y_value" is contiguous, with 0b000 corresonding to Y0 and 0b111 corresponding to Y7

  // This loop pair will ensure everything is initialized to NOT CONNECTED the very first time it runs.
  // It will look like a whole bunch of nothing is happening on the Serial port.
 for(int y = 0; y < 8; y++){  //this is a nested for loop where for each y it does each x. Set up the Y Loop
    int y_value = y;
    for(int x = 0; x < 8; x += 1){  // Set up X Loop
      int x_value = x;      
      write_data(false,x_value,y_value);
      // read_data(1);
      // read_data(2);
      // read_data(3);
      // read_data(4);
      // read_data(5);
      // read_data(6);
      // read_data(7);
      // read_data(8);
    }
  }
  String m_chip_wiped = "Chip wiped";
  String output_message = m_chip_wiped + millis(); //this take on average 9 millsecs without printing to serial.
  Serial.println(output_message);
}

void AGD2188::ArrayToWrite(int input_array[8], int sizeOfArray){
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
         write_data(true,7,i);
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
          write_data(true,l,o);
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
      write_data(true,m,7);
    }
  }
} 
//////////////////////////////////////////////////////////////

void AGD2188::test_chip(){
 for (int i =0; i<8; i++){
    for (int j =0; j<8; j++){
      write_data(true,i,j);
      read_data(i);
      delay(500);
    }
  }
  wipe_chip();
}
