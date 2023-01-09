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
    void setSaveFileName(String fileName);
    bool checkForSaveFile();
    int getPrevBankId();
	private:
    int chipSelectPin;
    String bankSaveFileName;
    const char * bankSaveFileName_cc;
    char * bankSaveFileName_c;

};
 
#endif
