#ifndef NEXTION_COMMANDS
#define NEXTION_COMMANDS

#include <Arduino.h>

//---------For Nextion Display -----------
const byte END_BYTE = 0xff;
const String STEREO = "S";
const String MONO = "M";


//A
const String A_LOOP_POS = "A_LOOP_POS";
const String INPUT_A_VOLUME = "A_VOL_IN";
const String OUTPUT_A_VOLUME = "A_VOL_OUT";
const String LEFT_A_PHASE = "A_L_PHASE";
const String RIGHT_A_PHASE = "A_R_PHASE";
//Phase Display
const String A_PHASE_IN = "A";
const String A_PHASE_OUT = "a";
//
const String A_RETURN = "A_RETURN";
const String PAN_A = "A_PAN";

//B
const String B_LOOP_POS = "B_LOOP_POS";
const String INPUT_B_VOLUME = "B_VOL_IN";
const String OUTPUT_B_VOLUME = "B_VOL_OUT";
const String LEFT_B_PHASE = "B_L_PHASE";
const String RIGHT_B_PHASE = "B_R_PHASE";
  //Phase Display
const String B_PHASE_IN = "B";
const String B_PHASE_OUT = "b";
//
const String B_RETURN = "B_RETURN";
const String PAN_B = "B_PAN";


//C
const String C_LOOP_POS = "C_LOOP_POS";
const String INPUT_C_VOLUME = "C_VOL_IN";
const String OUTPUT_C_VOLUME = "C_VOL_OUT";
const String LEFT_C_PHASE = "C_L_PHASE";
const String RIGHT_C_PHASE = "C_R_PHASE";
  //Phase Display
const String C_PHASE_IN = "C";
const String C_PHASE_OUT = "c";
//
const String C_RETURN = "C_RETURN";
const String PAN_C = "C_PAN";

//D
const String D_LOOP_POS = "D_LOOP_POS";
const String INPUT_D_VOLUME = "D_VOL_IN";
const String OUTPUT_D_VOLUME = "D_VOL_OUT";
const String LEFT_D_PHASE = "D_L_PHASE";
const String RIGHT_D_PHASE = "D_R_PHASE";
  //Phase Display
const String D_PHASE_IN = "D";
const String D_PHASE_OUT = "d";
//
const String D_RETURN = "D_RETURN";
const String PAN_D = "D_PAN";

//E
const String E_LOOP_POS = "E_LOOP_POS";
const String INPUT_E_VOLUME = "E_VOL_IN";
const String OUTPUT_E_VOLUME = "E_VOL_OUT";
const String LEFT_E_PHASE = "E_L_PHASE";
const String RIGHT_E_PHASE = "E_R_PHASE";
  //Phase Display
const String E_PHASE_IN = "E";
const String E_PHASE_OUT = "e";
//
const String E_RETURN = "E_RETURN";
const String PAN_E = "E_PAN";

//F
const String F_LOOP_POS = "F_LOOP_POS";
const String INPUT_F_VOLUME = "F_VOL_IN";
const String OUTPUT_F_VOLUME = "F_VOL_OUT";
const String LEFT_F_PHASE = "F_L_PHASE";
const String RIGHT_F_PHASE = "F_R_PHASE";
  //Phase Display
const String F_PHASE_IN = "F";
const String F_PHASE_OUT = "f";
//
const String F_RETURN = "F_RETURN";
const String PAN_F = "F_PAN";

//G 
const String G_LOOP_POS = "G_LOOP_POS";
const String INPUT_G_VOLUME = "G_VOL_IN";
const String OUTPUT_G_VOLUME = "G_VOL_OUT";
const String LEFT_G_PHASE = "G_L_PHASE";
const String RIGHT_G_PHASE = "G_R_PHASE";
  //Phase Display
const String G_PHASE_IN = "G";
const String G_PHASE_OUT = "g";
//
const String G_RETURN = "G_RETURN";
const String PAN_G = "G_PAN";

//Main
const String INPUT_MAIN_VOLUME = "M_VOL_IN";
const String OUTPUT_MAIN_VOLUME = "M_VOL_OUT";
const String PAN_MAIN = "M_PAN";

String ADDRESS_FOR_DISPLAY[8][6] = {
// ADDRESS IN NEXTION 
//IN VOL(0)           OUT VOL(1)           RETURN(2)  PAN(3)    LEFT(4)        RIGHT(5)    
  {INPUT_A_VOLUME,    OUTPUT_A_VOLUME,     A_RETURN  ,PAN_A,    LEFT_A_PHASE,  RIGHT_A_PHASE   },
  {INPUT_B_VOLUME,    OUTPUT_B_VOLUME,     B_RETURN  ,PAN_B,    LEFT_B_PHASE,  RIGHT_B_PHASE   },
  {INPUT_C_VOLUME,    OUTPUT_C_VOLUME,     C_RETURN  ,PAN_C,    LEFT_C_PHASE,  RIGHT_C_PHASE   },
  {INPUT_D_VOLUME,    OUTPUT_D_VOLUME,     D_RETURN  ,PAN_D,    LEFT_D_PHASE,  RIGHT_D_PHASE   },
  {INPUT_E_VOLUME,    OUTPUT_E_VOLUME,     E_RETURN  ,PAN_E,    LEFT_E_PHASE,  RIGHT_E_PHASE   },
  {INPUT_F_VOLUME,    OUTPUT_F_VOLUME,     F_RETURN  ,PAN_F,    LEFT_F_PHASE,  RIGHT_F_PHASE   },
  {INPUT_G_VOLUME,    OUTPUT_G_VOLUME,     G_RETURN  ,PAN_G,    LEFT_G_PHASE,  RIGHT_G_PHASE   },
  {INPUT_MAIN_VOLUME, OUTPUT_MAIN_VOLUME,  "null"   , PAN_MAIN, "null"   ,     "null"          } };

// needs just input and output volume instaed of left right, needs to add pan

const String PHASES_FOR_DISPLAY[7][2] = {
  // IN(0)          OUT(1)
  {A_PHASE_IN,  A_PHASE_OUT},
  {B_PHASE_IN,  B_PHASE_OUT},
  {C_PHASE_IN,  C_PHASE_OUT},
  {D_PHASE_IN,  D_PHASE_OUT},
  {E_PHASE_IN,  E_PHASE_OUT},
  {F_PHASE_IN,  F_PHASE_OUT},
  {G_PHASE_IN,  G_PHASE_OUT}
  };

const String LOOPS_FOR_DISPLAY[7] = {A_LOOP_POS, B_LOOP_POS,C_LOOP_POS,D_LOOP_POS,E_LOOP_POS,F_LOOP_POS,G_LOOP_POS};

const String FOOT_BANKS[5] = {"A","B","C","D","E"};

//-----------------SCREENS-------------------
const String HOME_PAGE = "page main";
const String FOOTSWITCH_PAGE = "page switchBank";
const String TITLE_PAGE = "page title";
const String SPACE_BACKGROUND = "page space";

 #endif //!NEXTION_COMMANDS