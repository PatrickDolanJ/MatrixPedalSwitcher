// things to add. hardcoded ummmm bits for each x and y address. this would allow you to pass human readable numbers, x and y numbers
// currently you have to construct the byte 
// https://www.farnell.com/datasheets/1793938.pdf
#include <Wire.h>
#include <matrix_library.h>
#include <Arduino.h>

//const byte AGD2188_ADDRESS = 0x71;  //Arduino uses 7 bit addresses. this probably means that arduino 
//only has 128 possible adress that it can write to. you probably have to drop the least signifigant bit 
//which we guess means we drop the highest bit meaning the one all the way to the left. If you have 
//an 8 bit address, drop the LSB and shift right
//const byte NOW = 0x01;
// 0x71 remember that 0x just neans its a hex number and the two following digits are the actual hex 71 = 1110001
// in the datasheet figure 33, this matches the A0-A2 address bytes

// Lay out the constants for reading back the switch states
// const byte X0 = 0x34;
// const byte X1 = 0x3C;
// const byte X2 = 0x74;
// const byte X3 = 0x7C;
// const byte X4 = 0x35;
// const byte X5 = 0x3D;
// const byte X6 = 0x75;
// const byte X7 = 0x7D;
//Making the first bit to tell to turn off or on connection
// const byte ON_BIT = 0b1;
// const byte OFF_BIT = 0b0;
//////////////////////////

// //Settign up x array for converting to BYTE
// const byte W_X0 = 0b0000;
// const byte W_X1 = 0b0001;
// const byte W_X2 = 0b0010;
// const byte W_X3 = 0b0011;
// const byte W_X4 = 0b0100;
// const byte W_X5 = 0b0101;
// const byte W_X6 = 0b1000;
// const byte W_X7 = 0b0001;

//const byte x_byte_array[8] = {W_X0,W_X1,W_X2,W_X3,W_X4,W_X5,W_X6,W_X7};
/////////////////

// //Setting up y adress for converting to BYTE
// const byte W_Y0 = 0b000;
// const byte W_Y1 = 0b001;
// const byte W_Y2 = 0b010;
// const byte W_Y3 = 0b011;
// const byte W_Y4 = 0b100;
// const byte W_Y5 = 0b101;
// const byte W_Y6 = 0b110;
// const byte W_Y7 = 0b111;

//const byte y_byte_array[8]= {W_Y0,W_Y1,W_Y2,W_Y3,W_Y4,W_Y5,W_Y6,W_Y7};
///////////////////
AGD2188::AGD2188()
{
  Wire.begin(); // join i2c bus (address optional for master)
  //Serial.begin(115200);
}

//void loop()
//{
  // This pair of loops is identical to the above, except it adds 128 to the value to signify the "ON" state.
//   for(int y = 0; y < 8; y++){
//     byte y_value = y;
//     for(int x = 0; x < 8; x += 1){
//       byte x_value;
//       int send_value;      
//       if (x >= 6){
//         x_value = x + 2;
//       }
//       else {
//         x_value = x;
//       }      
//       send_value = x_value*8+y_value+128;  // Add 128 here to toggle "ON" (DATA bit in Table 7)
//       write_data(send_value);

//       Serial.print("Wrote ");
//       Serial.println(send_value);
      
//       read_data(X0);
//       read_data(X1);
//       read_data(X2);
//       read_data(X3);
//       read_data(X4);
//       read_data(X5);
//       read_data(X6);
//       read_data(X7);
//       delay(100);
//     }
//   }
//}

  byte AGD2188::convert_to_byte(bool OnOrOff, int x, int y){
    byte x_byte = x_byte_array[x-1];
    byte y_byte = y_byte_array[y-1];
    byte OnOrOff_byte = 0b0;

    if(OnOrOff){
        OnOrOff_byte = ON_BIT;
    } else {
        OnOrOff_byte = OFF_BIT;
    }
    byte write_converted = OnOrOff_byte << 7 | x_byte << 3 | y_byte;
    return write_converted;
}

void AGD2188::read_data(int x){  ///currently set to void but might be benefitial to return array of connections. 
  const byte read_byte = 0xE3; // write_data(x_address);   this needs the initial byte to be in READ MODE, then it needs the alternate X code as in Table 8.
  byte data_array[2];   //first needs to write x_adress, then 
  data_array[0] = read_byte;
  data_array[1] = x_byte_array[x-1]; // THIS NEEDS TO BE FIXED \\
  Wire.beginTransmission(read_byte);

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
}

// To execute a read, you first have to WRITE the address value to the device.
// The second byte of the write is DON'T CARE, but it is necessary.  So we leave it as the "NOW" byte.
// After you setup the read address, all you have to do is request 2 bytes.  The first byte is always all "0".
// (See bottom trace in Figure 35)

void AGD2188::wipe_chip()
{
  // These FOR loops will cycle from X0 - Y0 to X7 - Y7
  // The "x_value" is derived from Table 7 (AX3-AX0).  Note that it's not contiguous because they reserve
  // values for the read register values (seen above).  Kind of a pain.
  // The "y_value" is contiguous, with 0b000 corresonding to Y0 and 0b111 corresponding to Y7

  // This loop pair will ensure everything is initialized to NOT CONNECTED the very first time it runs.
  // It will look like a whole bunch of nothing is happening on the Serial port.
 for(int y = 0; y < 8; y++){  //this is a nested for loop where for each y it does each x. Set up the Y Loop
    byte y_value = y;
    for(int x = 0; x < 8; x += 1){  // Set up X Loop
      byte x_value;
      int send_value;      
      if (x >= 6){             //so this is all to deal with the "reserved" in figure 7 not 8
        x_value = x + 2;       //jump ahead to skip over resserved 
      }
      else {
        x_value = x;
      }
      
      send_value = x_value*8+y_value;
      write_data(false,0,0);
      Serial.print("Wrote ");
      Serial.println(send_value);      
      read_data(X0);
      read_data(X1);
      read_data(X2);
      read_data(X3);
      read_data(X4);
      read_data(X5);
      read_data(X6);
      read_data(X7);
      delay(100);
    }
  }
}

