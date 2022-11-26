///------------------------
//AD5206 Digital Pots DataSheet: https://www.analog.com/media/en/technical-documentation/data-sheets/AD5204_5206.pdf
//
// Library made by: Patrick Dolan
// Credit: Ian Edwards
//-------------------------


//-------------------INPUT VOLUMES--------------------

const int INPUT_VOLUMES_POTS_IDS[2][8] = {
//A, B,  C,  D,  E,  F,  G, MASTER
 {1, 5,  9, 13, 17, 21,  25, 29}, //LEFT
 {2, 6, 10, 14, 18, 22,  26, 30} //RIGHT
}; 

//-------------------OUTPUT VOLUMES--------------------

const int LEFT_OUTPUT_VOLUMES_POTS_IDS[8] = {
//A, B,  C,  D,  E,  F,  G, MASTER
3, 7, 11, 15, 19, 23, 27, 31};

const int RIGHT_OUTPUT_VOLUMES_POTS_IDS[8] = {
//A, B,  C,  D,  E,  F,  G, MASTER
4, 8, 12, 16, 20, 24, 28, 32
};


void digitalPotWrite(int pot, int value){
  if(pot <= 5){
    digitalWrite(cs0_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs0_pin, HIGH);
  }
  if(pot >= 6 || pot <= 11){
    digitalWrite(cs1_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 6);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs1_pin, HIGH);
  }
  if(pot >= 12 || pot <= 17){
    digitalWrite(cs2_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 12);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs2_pin, HIGH);
  }
  if(pot >= 18 || pot <= 23){
    digitalWrite(cs3_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 18);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs3_pin, HIGH);
  }
  if(pot >= 24 || pot <= 29){
    digitalWrite(cs4_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 24);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs4_pin, HIGH);
  }
  if(pot >= 30 || pot <= 35){
    digitalWrite(cs5_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 30);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs5_pin, HIGH);
  }
}