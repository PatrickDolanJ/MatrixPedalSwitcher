#ifndef NEXTION_COMMANDS
#define NEXTION_COMMANDSD

#include <Arduino.h>

//---------Display Objects -----------
const static char _NAME[] PROGMEM = "_NAME";
const static char _RETURN[] PROGMEM = "_RETURN";
const static char _LEFT_PHASE[] PROGMEM = "_L_PHASE";
const static char _RIGHT_PHASE[] PROGMEM = "_R_PHASE";
const static char _LOOP_POS[] PROGMEM = "_LOOP_POS";
const static char _PAN[] PROGMEM = "_PAN";
const static char _INPUT_VOLUME[] PROGMEM = "_VOL_IN";
const static char _OUTPUT_VOLUME[] PROGMEM = "_VOL_OUT";
const static char MENU_STATE_FOR_DISPLAY[] PROGMEM = "CURRENT_PARAM";
const static char BANK_NUMBER[] PROGMEM = "BANK_NUMBER";
const static char PRESET_LETTER[] PROGMEM = "FOOT_LETTER";
const static char DATA_CHANGED[] PROGMEM = "PRESET_TOGGLE";
const static char FOOT_BANK_NUM[] PROGMEM = "FOOT_BANK_NUM";

//-------------Values-----------------
const byte END_BYTE = 0xff;
const static char STEREO[] PROGMEM = "S";
const static char MONO[] PROGMEM = "M";
const static char IN_PHASE[] PROGMEM = "I";
const static char OUT_OF_PHASE[] PROGMEM = "O";
const static char IS_DELAY_TRAIL[] PROGMEM = ">";
const static char IS_NOT_DELAY_TRAIL[] PROGMEM = "";
const static char NO_DRY_SEND[] PROGMEM = "";

const String LOOP_NAMES[8] = {"A", "B", "C", "D", "E", "F", "G", "M"};
const String FOOT_PRESETS[5] = {"A", "B", "C", "D", "E"};

const static char MENU_STATE_LOOPS[] PROGMEM = "LOOP  ORDER";
const static char MENU_STATE_PAN[] PROGMEM = "OUTPUT  PAN";
const static char MENU_STATE_INPUT_VOLUMES[] PROGMEM = "INPUT  VOLUME";
const static char MENU_STATE_OUTPUT_VOLUMES[] PROGMEM = "OUTPUT  VOLUME";
const static char MENU_STATE_PHASE[] PROGMEM = "PHASE";
const static char MENU_STATE_RETURN[] PROGMEM = "MONO/STEREO";
const static char MENU_STATE_DELAY_TRAILS[] PROGMEM = "DELAY TRAILS";

//-----------------SCREENS-------------------
const static char HOME_PAGE[] PROGMEM = "main";
const static char BANK_SELECTION_PAGE[] PROGMEM = "switchBank";
const static char TITLE_PAGE[] PROGMEM = "title";
const static char SPACE_BACKGROUND[] PROGMEM = "space";
const static char SAVE_PAGE[] PROGMEM = "savePage";

#endif //! NEXTION_COMMANDS