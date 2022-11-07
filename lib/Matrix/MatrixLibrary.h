#ifndef matrix_library
#define matrix_library
 
#include <Arduino.h>

class AGD2188
{
	public:
	AGD2188(); // default constructor addresses 1110000 adress
	AGD2188(byte address); // non default allows 0-7 AGD2188
	void wipeChip();
	void writeData(bool OnorOff, int x, int y);
	void readData(int x);
	void writeArray(int input_array[8], int sizeOfArray);
	void testChip();
	private:
	byte matrix_address;
};
 
#endif