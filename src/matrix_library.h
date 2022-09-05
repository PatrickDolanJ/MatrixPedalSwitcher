#ifndef Blink_h
#define Blink_h
 
#include <Arduino.h>

class AGD2188
{
	public:
	AGD2188();
	void wipe_chip();
	void write_data(bool OnorOff, int x, int y);
	void read_date();

	private:
	const byte AGD2188_ADDRESS = 0x71; 
	const byte NOW = 0x01;
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
	//Settign up x array for converting to BYTE
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
	//Setting up y adress for converting to BYTE
	const byte W_Y0 = 0b000;
	const byte W_Y1 = 0b001;
	const byte W_Y2 = 0b010;
	const byte W_Y3 = 0b011;
	const byte W_Y4 = 0b100;
	const byte W_Y5 = 0b101;
	const byte W_Y6 = 0b110;
	const byte W_Y7 = 0b111;
	const byte y_byte_array[8]= {W_Y0,W_Y1,W_Y2,W_Y3,W_Y4,W_Y5,W_Y6,W_Y7};
	///////////////////
	

};
 
#endif