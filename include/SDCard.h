#ifndef sd_card_inteface    
#define sd_card_inteface
 
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class SDCard
{
	public:
    SDCard(int chipSelectPin);
    void begin();
    void readTestFile();
	private:
    int chipSelectPin;
    File myfile;
};
 
#endif
