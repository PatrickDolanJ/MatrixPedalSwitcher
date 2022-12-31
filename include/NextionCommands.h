#ifndef NEXTION_COMMANDS
#define NEXTION_COMMANDS

#include <Arduino.h>
// This could be refactored to somethign like array of channel IDS aka A,B,C
// and then concactenated with somethine like L_PHASE aka "A" + "_L_PHASE"

//---------For Nextion Display -----------
const byte END_BYTE = 0xff;
const String STEREO = "S";
const String MONO = "M";
const String IN_PHASE = "I";
const String OUT_OF_PHASE = "O";

// A
const String A_NAME = "A_NAME";
const String A_RETURN = "A_RETURN";
const String LEFT_A_PHASE = "A_L_PHASE";
const String RIGHT_A_PHASE = "A_R_PHASE";
const String A_LOOP_POS = "A_LOOP_POS";
const String PAN_A = "A_PAN";
const String INPUT_A_VOLUME = "A_VOL_IN";
const String OUTPUT_A_VOLUME = "A_VOL_OUT";

// B
const String B_NAME = "B_NAME";
const String B_RETURN = "B_RETURN";
const String LEFT_B_PHASE = "B_L_PHASE";
const String RIGHT_B_PHASE = "B_R_PHASE";
const String B_LOOP_POS = "B_LOOP_POS";
const String PAN_B = "B_PAN";
const String INPUT_B_VOLUME = "B_VOL_IN";
const String OUTPUT_B_VOLUME = "B_VOL_OUT";

// C
const String C_NAME = "C_NAME";
const String C_RETURN = "C_RETURN";
const String LEFT_C_PHASE = "C_L_PHASE";
const String RIGHT_C_PHASE = "C_R_PHASE";
const String C_LOOP_POS = "C_LOOP_POS";
const String PAN_C = "C_PAN";
const String INPUT_C_VOLUME = "C_VOL_IN";
const String OUTPUT_C_VOLUME = "C_VOL_OUT";

// D
const String D_NAME = "D_NAME";
const String D_RETURN = "D_RETURN";
const String LEFT_D_PHASE = "D_L_PHASE";
const String RIGHT_D_PHASE = "D_R_PHASE";
const String D_LOOP_POS = "D_LOOP_POS";
const String PAN_D = "D_PAN";
const String INPUT_D_VOLUME = "D_VOL_IN";
const String OUTPUT_D_VOLUME = "D_VOL_OUT";

// E
const String E_NAME = "E_NAME";
const String E_RETURN = "E_RETURN";
const String LEFT_E_PHASE = "E_L_PHASE";
const String RIGHT_E_PHASE = "E_R_PHASE";
const String E_LOOP_POS = "E_LOOP_POS";
const String PAN_E = "E_PAN";
const String INPUT_E_VOLUME = "E_VOL_IN";
const String OUTPUT_E_VOLUME = "E_VOL_OUT";

// F
const String F_NAME = "F_NAME";
const String F_RETURN = "F_RETURN";
const String F_LOOP_POS = "F_LOOP_POS";
const String LEFT_F_PHASE = "F_L_PHASE";
const String RIGHT_F_PHASE = "F_R_PHASE";
const String PAN_F = "F_PAN";
const String INPUT_F_VOLUME = "F_VOL_IN";
const String OUTPUT_F_VOLUME = "F_VOL_OUT";

// G
const String G_NAME = "G_NAME";
const String G_RETURN = "G_RETURN";
const String LEFT_G_PHASE = "G_L_PHASE";
const String RIGHT_G_PHASE = "G_R_PHASE";
const String G_LOOP_POS = "G_LOOP_POS";
const String PAN_G = "G_PAN";
const String INPUT_G_VOLUME = "G_VOL_IN";
const String OUTPUT_G_VOLUME = "G_VOL_OUT";

// Main
const String MASTER_NAME = "M_NAME";
const String MASTER_RETURN = "M_RETURN";
const String DRY_SEND = "M_LOOP_POS";
const String PAN_MASTER = "M_PAN";
const String INPUT_MASTER_VOLUME = "M_VOL_IN";
const String OUTPUT_MASTER_VOLUME = "M_VOL_OUT";

const String NAMES_FOR_DISPLAY[8] = {A_NAME,B_NAME,C_NAME,D_NAME,E_NAME,F_NAME,G_NAME,MASTER_NAME};
const String RETURNS_FOR_DISPLAY[8] = {A_RETURN,B_RETURN,C_RETURN,D_RETURN,E_RETURN,F_RETURN,G_RETURN,MASTER_RETURN};
const String LEFT_PHASES_FOR_DISPLAY[7] = {LEFT_A_PHASE,LEFT_B_PHASE,LEFT_C_PHASE,LEFT_D_PHASE,LEFT_E_PHASE,LEFT_F_PHASE,LEFT_G_PHASE};
const String RIGHT_PHASES_FOR_DISPLAY[7] = {RIGHT_A_PHASE,RIGHT_B_PHASE,RIGHT_C_PHASE,RIGHT_D_PHASE,RIGHT_E_PHASE,RIGHT_F_PHASE,RIGHT_G_PHASE};
const String LOOPS_FOR_DISPLAY[7] = {A_LOOP_POS, B_LOOP_POS, C_LOOP_POS, D_LOOP_POS, E_LOOP_POS, F_LOOP_POS, G_LOOP_POS};
const String PANS_FOR_DISPLAY[8] = {PAN_A,PAN_B,PAN_C,PAN_D,PAN_E,PAN_F,PAN_G,PAN_MASTER};
const String INPUT_VOLUMES_FOR_DISPLAY[8] = {INPUT_A_VOLUME,INPUT_B_VOLUME,INPUT_C_VOLUME,INPUT_D_VOLUME,INPUT_E_VOLUME,INPUT_F_VOLUME,INPUT_G_VOLUME,INPUT_MASTER_VOLUME}; 
const String OUTPUT_VOLUMES_FOR_DISPLAY[8] = {OUTPUT_A_VOLUME,OUTPUT_B_VOLUME,OUTPUT_C_VOLUME,OUTPUT_D_VOLUME,OUTPUT_E_VOLUME,OUTPUT_F_VOLUME,OUTPUT_G_VOLUME,OUTPUT_MASTER_VOLUME};

const String FOOT_BANKS[5] = {"A", "B", "C", "D", "E"};

const String MENU_STATE_LOOPS = "LOOP ORDER";
const String MENU_STATE_PAN = "OUTPUT PAN";
const String MENU_STATE_INPUT_VOLUMES = "INPUT VOLUME";
const String MENU_STATE_OUTPUT_VOLUME = "OUTPUT VOLUME";
const String MENU_STATE_PHASE = "PHASE";

//-----------------SCREENS-------------------
const String HOME_PAGE = "main";
const String FOOTSWITCH_PAGE = "switchBank";
const String TITLE_PAGE = "title";
const String SPACE_BACKGROUND = "space";

#endif //! NEXTION_COMMANDS