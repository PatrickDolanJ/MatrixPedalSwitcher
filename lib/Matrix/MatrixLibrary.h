#ifndef matrix_library
#define matrix_library
 
#include <Arduino.h>

class AGD2188
{
	public:
	AGD2188();
	void wipe_chip();
	void write_data(bool OnorOff, int x, int y);
	void read_data(int x);

	private:
	byte convert_to_byte(bool OnOrOff, int x, int y);
};
 
#endif