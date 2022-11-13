#include <Arduino.h> 

//--------------Settings---------------
const String DEVICE_NAME = "HeighLiner";
const int DEFAULT_VOLUME = 125;
const String DEFAULT_COLOR = "19703";
const String HIGHLIGHT_COLOR = "65535"; 
const float LONG_PRESS_INTERVAL_S = 1.75;

//------------I2C Addresses-------------
const byte ROTARY_BUTTONS_ADDRESS = 0x21;
const byte FOOTSWITCH_ADDRESS = 0x22;
const byte RIGHT_MATRIX_ADDRESS = 0x70;
const byte LEFT_MATRIX_ADDRESS = 0x74;

//-------------Interupts----------------
const int ROTARY_INTERUPT_PIN = 3; 
const int FOOT_INTERUPT_PIN = 18; 
const int ROTARY_ENCODER_INTERUPT_PIN = 2;

//-------------Digital Pots-------------
const int spiDelay = 1;
const int cs0_pin = 32;
const int cs1_pin = 33;
const int cs2_pin = 34;
const int cs3_pin = 35;
const int cs4_pin = 36;
const int cs5_pin = 37;