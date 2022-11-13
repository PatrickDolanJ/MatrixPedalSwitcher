/*
Created by: PatrickDolanJ
Based On: josh_d : https://forum.arduino.cc/t/writing-to-adg2188-switch-array-via-i2c/272611/6
*/

/*---------------DATASHEET----------------------
  https://www.farnell.com/datasheets/1793938.pdf
-----------------------------------------------*/

#ifndef matrix_library
#define matrix_library
 
#include <Arduino.h>

class AGD2188
{
	public:
	AGD2188(); // default constructor addresses 0x70 adress
	AGD2188(byte address); // non default allows up to 8 AGD2188
	void wipeChip();
	void writeData(bool OnorOff, int x, int y);
	void readData(int x);
	void writeArray(int input_array[8], int sizeOfArray);
	void testChip();
	private:
	byte matrix_address;
};
 
#endif