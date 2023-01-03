#ifndef NEXTION_COMMANDS
#define NEXTION_COMMANDS

#include <Arduino.h>

//---------Display Objects -----------
const  String _NAME = "_NAME";
const String _RETURN = "_RETURN";
const String _LEFT_PHASE = "_L_PHASE";
const String _RIGHT_PHASE = "_R_PHASE";
const String _LOOP_POS = "_LOOP_POS";
const String _PAN = "_PAN";
const String _INPUT_VOLUME = "_VOL_IN";
const String _OUTPUT_VOLUME = "_VOL_OUT";
const String MENU_STATE_FOR_DISPLAY = "CURRENT_PARAM";
const String BANK_NUMBER = "BANK_NUMBER";
const String PRESET_LETTER = "FOOT_LETTER";

//-------------Values-----------------
const byte END_BYTE = 0xff;
const String STEREO = "S";
const String MONO = "M";
const String IN_PHASE = "I";
const String OUT_OF_PHASE = "O";
const String IS_DELAY_TRAIL = "";
const String IS_NOT_DELAY_TRAIL = "";

const String LOOP_NAMES[8] = {"A", "B", "C", "D", "E", "F", "G", "M"};
const String FOOT_PRESETS[5] = {"A", "B", "C", "D", "E"};

const String MENU_STATE_LOOPS = "LOOP  ORDER";
const String MENU_STATE_PAN = "OUTPUT  PAN";
const String MENU_STATE_INPUT_VOLUMES = "INPUT  VOLUME";
const String MENU_STATE_OUTPUT_VOLUMES = "OUTPUT  VOLUME";
const String MENU_STATE_PHASE = "PHASE";

//-----------------SCREENS-------------------
const String HOME_PAGE = "main";
const String FOOTSWITCH_PAGE = "switchBank";
const String TITLE_PAGE = "title";
const String SPACE_BACKGROUND = "space";

#endif //! NEXTION_COMMANDS