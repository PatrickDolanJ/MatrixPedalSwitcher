#ifndef matrix_library
#define matrix_library
 
#include <Arduino.h>

class AGD2188
{
	public:
	AGD2188(); // default constructor addresses 1110000 adress
	AGD2188(int address); // non default allows 0-7 AGD2188
	void wipe_chip();
	void write_data(bool OnorOff, int x, int y);
	void read_data(int x);
	void ArrayToWrite(int input_array[8], int sizeOfArray);
	void test_chip();

	private:
	//byte convert_to_byte(bool OnOrOff, int x, int y);
};
 
#endif