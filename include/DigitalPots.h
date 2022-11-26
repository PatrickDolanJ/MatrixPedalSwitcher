// ///------------------------
// //AD5206 Digital Pots DataSheet: https://www.analog.com/media/en/technical-documentation/data-sheets/AD5204_5206.pdf
// //
// // Library made by: Patrick Dolan and Ian Edwards
// //-------------------------


// //-------------------INPUT VOLUMES--------------------

// const int INPUT_VOLUMES_POTS_IDS[2][8] = {
// //A, B,  C,  D,  E,  F,  G, MASTER
//  {1, 5,  9, 13, 17, 21, 25, 29}, //LEFT
//  {2, 6, 10, 14, 18, 22, 26, 30} //RIGHT
// }; 

// //-------------------OUTPUT VOLUMES--------------------

// const int LEFT_OUTPUT_VOLUMES_POTS_IDS[8] = {
// //A, B,  C,  D,  E,  F,  G, MASTER
// 3, 7, 11, 15, 19, 23, 27, 31};

// const int RIGHT_OUTPUT_VOLUMES_POTS_IDS[8] = {
// //A, B,  C,  D,  E,  F,  G, MASTER
// 4, 8, 12, 16, 20, 24, 28, 32};


// void digitalPotWrite(int pot, int value){
//   int interalPotID = (pot-1)%6;
//   Serial.println("Pot Value whole: " + String(pot));
//   Serial.println("Pot Value minus 1 : " + String(pot-1));
//   Serial.println("Modulus internal: " + String(interalPotID));
//   Serial.println("Volume Value: " + String(value));

//   if(pot <= 5){
//     digitalWrite(cs0_pin, LOW);
//     delayMicroseconds(spiDelay);
//     SPI.transfer(interalPotID);
//     SPI.transfer(value);
//     delayMicroseconds(spiDelay);
//     digitalWrite(cs0_pin, HIGH);
//     Serial.println("Pot 1");
//   }
//   if(pot >= 6 && pot <= 11){
//     digitalWrite(cs1_pin, LOW);
//     delayMicroseconds(spiDelay);
//     SPI.transfer(interalPotID);
//     SPI.transfer(value);
//     delayMicroseconds(spiDelay);
//     digitalWrite(cs1_pin, HIGH);
//     Serial.println("Pot 2");
//   }
//   if(pot >= 12 && pot <= 17){
//     digitalWrite(cs2_pin, LOW);
//     delayMicroseconds(spiDelay);
//     SPI.transfer(interalPotID);
//     SPI.transfer(value);
//     delayMicroseconds(spiDelay);
//     digitalWrite(cs2_pin, HIGH);
//     Serial.println("Pot 3");
//   }
//   if(pot >= 18 && pot <= 23){
//     digitalWrite(cs3_pin, LOW);
//     delayMicroseconds(spiDelay);
//     SPI.transfer(interalPotID);
//     SPI.transfer(value);
//     delayMicroseconds(spiDelay);
//     digitalWrite(cs3_pin, HIGH);
//   }
//   if(pot >= 24 && pot <= 29){
//     digitalWrite(cs4_pin, LOW);
//     delayMicroseconds(spiDelay);
//     SPI.transfer(interalPotID);
//     SPI.transfer(value);
//     delayMicroseconds(spiDelay);
//     digitalWrite(cs4_pin, HIGH);
//     Serial.println("Pot 4");
//   }
//   if(pot >= 30 && pot <= 35){
//     digitalWrite(cs5_pin, LOW);
//     delayMicroseconds(spiDelay);
//     SPI.transfer(interalPotID);
//     SPI.transfer(value);
//     delayMicroseconds(spiDelay);
//     digitalWrite(cs5_pin, HIGH);
//     Serial.println("Pot 5");
//   }
// }

#include <Arduino.h>

const int potID[6] = {cs0_pin,cs1_pin,cs2_pin,cs3_pin,cs4_pin,cs5_pin};

//void digitalWritePot(int potID, int internalPotID, int value);

const String LOOP_NAMES[8] = {"A", "B", "C", "D", "E", "F", "G", "Master"};

const int LEFT_INPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 0, 4, 2, 0, 4, 2, 0, 4}, // Zero Indexed Internal Pot ID
  { 0, 0, 1, 2, 2, 3, 4, 4}  // Zero Indexed Pot ID for the Chip Select!!
};

const int RIGHT_INPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 1, 5, 3, 1, 5, 3, 1, 5},  // Zero Indexed Internal Pot ID
  { 0, 0, 1, 2, 2, 3, 4, 4}  // Zero Indexed Pot ID for the Chip Select!!
};
const int LEFT_OUTPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 2, 0, 4, 2, 0, 4, 2, 0},  // Zero Indexed Internal Pot ID
  { 0, 1, 1, 2, 3, 3, 4, 5}   // Zero Indexed Pot ID for the Chip Select!!
  };  

const int RIGHT_OUTPUT_VOLUME_POTS_IDS[2][8] = {
  //A, B, C, D, E, F, G, Master
  { 3, 1, 5, 3, 1, 5, 3, 1},  // Zero Indexed Internal Pot ID
  { 0, 1, 1, 2, 2, 3, 4, 5}   // Zero Indexed Pot ID for the Chip Select!!
  };  

// void setup() {
//   Serial.begin(115200);
//   // set the cs0_pin as an output:
//   pinMode(cs0_pin, OUTPUT);
//   pinMode(cs1_pin, OUTPUT);
//   pinMode(cs2_pin, OUTPUT);
//   pinMode(cs3_pin, OUTPUT);
//   pinMode(cs4_pin, OUTPUT);
//   pinMode(cs5_pin, OUTPUT);
//   // initialize SPI:
//   SPI.begin();
// }


// void loop() {
//   int potToTest = 1;
//   digitalWritePot(potID[LEFT_INPUT_VOLUME_POTS_IDS[1][potToTest]],LEFT_INPUT_VOLUME_POTS_IDS[0][potToTest],255);
//   Serial.println("Turning LEFT INPUT ON: " + LOOP_NAMES[potToTest]);
//   delay(5000);

//   digitalWritePot(potID[LEFT_INPUT_VOLUME_POTS_IDS[1][potToTest]],LEFT_INPUT_VOLUME_POTS_IDS[0][potToTest],0);
//   Serial.println("Turning LEFT INPUT OFF: " + LOOP_NAMES[potToTest]);
//   delay(5000);

// }

void digitalPotWrite(int potID, int internalPotID, int value){
digitalWrite(potID,LOW);
delayMicroseconds(spiDelay);
SPI.transfer(internalPotID);
SPI.transfer(value);
delayMicroseconds(spiDelay);
digitalWrite(potID, HIGH);

};


