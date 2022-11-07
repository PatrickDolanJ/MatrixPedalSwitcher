#include <Arduino.h> 

const String DEVICE_NAME = "HeighLiner";
const int DEFAULT_VOLUME = 125;
const String DEFAULT_COLOR = "19703";
const String HIGHLIGHT_COLOR = "62025"; 
const float LONG_PRESS_INTERVAL_S = 1.75;

const byte ROTARY_ADDRESS = 0x21;
const byte FOOTSWITCH_ADDRESS = 0x22;
const byte RIGHT_MATRIX_ADDRESS = 0x70;
const byte LEFT_MATRIX_ADDRESS = 0x74;

const int ROTARY_INTERUPT_PIN = 3; 
const int FOOT_INTERUPT_PIN = 18; 
const int ROTARY_ENCODER_INTERUPT_PIN = 2;