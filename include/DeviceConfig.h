#ifndef DEVICE_CONFIG
#define DEVICE_CONFIG

#include <Arduino.h>

//--------------Settings---------------
const String DEVICE_NAME = "HeighLiner";
const int MAX_VOLUME = 255;
const int DEFAULT_VOLUME = MAX_VOLUME;
const int VOLUME_DAMPENING_INCREMENTS = 100;
const int DEFAULT_PAN = 50; // 0(hard left) to 100 (hard right)
const int MAX_PAN = 100;
const String DEFAULT_COLOR = "19703";
const String HIGHLIGHT_COLOR = "65535";
const String DATA_CHANGED_COLOR = "62025";
const float LONG_PRESS_INTERVAL_S = 1.75;
const int SPI_DELAY = 1;
const unsigned long NEXTION_BAUD_RATE = 115200;
const int DOWN_ARROW_ID = 1;
const int UP_ARROW_ID = 0;
const int VOLUME_SCROLL_AMOUNT = 5;
const int PAN_SCROLL_AMOUNT = 5;
const int MAX_NUM_BANKS = 100;

//------------I2C Addresses-------------
const byte ROTARY_BUTTONS_ADDRESS = 0x21;
const byte FOOTSWITCH_ADDRESS = 0x22;
const byte FOOT_SWITCH_LIGHTS_ADDRESS = 0x23;
const byte RETURN_RELAYS_ADDRESS = 0x24;
const byte RIGHT_PHASE_RELAY_ADDRESS = 0x25;
const byte LEFT_PHASE_RELAYS_ADDRESS = 0x26;
const byte RIGHT_MATRIX_ADDRESS = 0x70;
const byte LEFT_MATRIX_ADDRESS = 0x74;

//-------------Interupts----------------
const int ROTARY_INTERUPT_PIN = 3;
const int FOOT_INTERUPT_PIN = 18;
const int ROTARY_ENCODER_INTERUPT_PIN = 2;

//-------------SPI CHIP SELECTS-------------
const int POT_EXPANDER_PIN_1 = 32;
const int POT_EXPANDER_PIN_2 = 33;
const int POT_EXPANDER_PIN_3 = 34;
const int POT_EXPANDER_PIN_4 = 35;
const int POT_EXPANDER_PIN_5 = 36;
const int POT_EXPANDER_PIN_6 = 37;

const int POT_EXPANDER_PINS[6] = {
    POT_EXPANDER_PIN_1,
    POT_EXPANDER_PIN_2,
    POT_EXPANDER_PIN_3,
    POT_EXPANDER_PIN_4,
    POT_EXPANDER_PIN_5,
    POT_EXPANDER_PIN_6};

const int SD_CARD_CHIP_SELECT_PIN = 38;

//-------------Foot Switches------------

#endif // !DEVICE_CONFIG