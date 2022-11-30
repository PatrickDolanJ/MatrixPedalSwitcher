#include <Arduino.h>

//---------For Nextion Display -----------
const byte b_end_message = 0xff;
const String STEREO = "S";
const String MONO = "M";
const String HOME_PAGE = "page 0";
const String SAVE_PRESET_PAGE = "page 1";
const String FOOTSWITCH_PAGE = "page 2";

//A
const String A_LOOP_POS = "A_LOOP_POS";
const String INPUT_A_LEFT = "A_L_VOL_IN";
const String INPUT_A_RIGHT = "A_R_VOL_IN";
const String OUTPUT_A_LEFT = "A_L_VOL_OUT";
const String OUTPUT_A_RIGHT = "A_R_VOL_OUT";
const String LEFT_A_PHASE = "A_L_PHASE";
const String RIGHT_A_PHASE = "A_R_PHASE";
//Phase Display
const String A_PHASE_IN = "A";
const String A_PHASE_OUT = "a";
//
const String A_RETURN = "A_RETURN";

//B
const String B_LOOP_POS = "B_LOOP_POS";
const String INPUT_B_LEFT = "B_L_VOL_IN";
const String INPUT_B_RIGHT = "B_R_VOL_IN";
const String OUTPUT_B_LEFT = "B_L_VOL_OUT";
const String OUTPUT_B_RIGHT = "B_R_VOL_OUT";
const String LEFT_B_PHASE = "B_L_PHASE";
const String RIGHT_B_PHASE = "B_R_PHASE";
  //Phase Display
const String B_PHASE_IN = "B";
const String B_PHASE_OUT = "b";
//
const String B_RETURN = "B_RETURN";


//C
const String C_LOOP_POS = "C_LOOP_POS";
const String INPUT_C_LEFT = "C_L_VOL_IN";
const String INPUT_C_RIGHT = "C_R_VOL_IN";
const String OUTPUT_C_LEFT = "C_L_VOL_OUT";
const String OUTPUT_C_RIGHT = "C_R_VOL_OUT";
const String LEFT_C_PHASE = "C_L_PHASE";
const String RIGHT_C_PHASE = "C_R_PHASE";
  //Phase Display
const String C_PHASE_IN = "C";
const String C_PHASE_OUT = "c";
//
const String C_RETURN = "C_RETURN";

//D
const String D_LOOP_POS = "D_LOOP_POS";
const String INPUT_D_LEFT = "D_L_VOL_IN";
const String INPUT_D_RIGHT = "D_R_VOL_IN";
const String OUTPUT_D_LEFT = "D_L_VOL_OUT";
const String OUTPUT_D_RIGHT = "D_R_VOL_OUT";
const String LEFT_D_PHASE = "D_L_PHASE";
const String RIGHT_D_PHASE = "D_R_PHASE";
  //Phase Display
const String D_PHASE_IN = "D";
const String D_PHASE_OUT = "d";
//
const String D_RETURN = "D_RETURN";

//E
const String E_LOOP_POS = "E_LOOP_POS";
const String INPUT_E_LEFT = "E_L_VOL_IN";
const String INPUT_E_RIGHT = "E_R_VOL_IN";
const String OUTPUT_E_LEFT = "E_L_VOL_OUT";
const String OUTPUT_E_RIGHT = "E_R_VOL_OUT";
const String LEFT_E_PHASE = "E_L_PHASE";
const String RIGHT_E_PHASE = "E_R_PHASE";
  //Phase Display
const String E_PHASE_IN = "E";
const String E_PHASE_OUT = "e";
//
const String E_RETURN = "E_RETURN";

//F
const String F_LOOP_POS = "F_LOOP_POS";
const String INPUT_F_LEFT = "F_L_VOL_IN";
const String INPUT_F_RIGHT = "F_R_VOL_IN";
const String OUTPUT_F_LEFT = "F_L_VOL_OUT";
const String OUTPUT_F_RIGHT = "F_R_VOL_OUT";
const String LEFT_F_PHASE = "F_L_PHASE";
const String RIGHT_F_PHASE = "F_R_PHASE";
  //Phase Display
const String F_PHASE_IN = "F";
const String F_PHASE_OUT = "f";
//
const String F_RETURN = "F_RETURN";

//G 
const String G_LOOP_POS = "G_LOOP_POS";
const String INPUT_G_LEFT = "G_L_VOL_IN";
const String INPUT_G_RIGHT = "G_R_VOL_IN";
const String OUTPUT_G_LEFT = "G_L_VOL_OUT";
const String OUTPUT_G_RIGHT = "G_R_VOL_OUT";
const String LEFT_G_PHASE = "G_L_PHASE";
const String RIGHT_G_PHASE = "G_R_PHASE";
  //Phase Display
const String G_PHASE_IN = "G";
const String G_PHASE_OUT = "g";
//
const String G_RETURN = "G_RETURN";

//Main
const String INPUT_MAIN_LEFT = "M_L_VOL_IN";
const String INPUT_MAIN_RIGHT = "M_R_VOL_IN";
const String OUTPUT_MAIN_LEFT = "M_L_VOL_OUT";
const String OUTPUT_MAIN_RIGHT = "M_R_VOL_OUT"; 

String ADDRESS_FOR_DISPLAY[8][7] = {
// ADDRESS IN NEXTION 
// LEFT IN VOL(0)   RIGHT IN VOL(1)    RETURN(2)  LEFT OUT VOL(3)       RIGHT OUT VOL(4)    LEFT PHASE(5)  RIGHT PHASE(6)    
  {INPUT_A_LEFT,    INPUT_A_RIGHT,     A_RETURN  ,OUTPUT_A_LEFT,        OUTPUT_A_RIGHT,    LEFT_A_PHASE,  RIGHT_A_PHASE   },
  {INPUT_B_LEFT,    INPUT_B_RIGHT,     B_RETURN  ,OUTPUT_B_LEFT,        OUTPUT_B_RIGHT,    LEFT_B_PHASE,  RIGHT_B_PHASE   },
  {INPUT_C_LEFT,    INPUT_C_RIGHT,     C_RETURN  ,OUTPUT_C_LEFT,        OUTPUT_C_RIGHT,    LEFT_C_PHASE,  RIGHT_C_PHASE   },
  {INPUT_D_LEFT,    INPUT_D_RIGHT,     D_RETURN  ,OUTPUT_D_LEFT,        OUTPUT_D_RIGHT,    LEFT_D_PHASE,  RIGHT_D_PHASE   },
  {INPUT_E_LEFT,    INPUT_E_RIGHT,     E_RETURN  ,OUTPUT_E_LEFT,        OUTPUT_E_RIGHT,    LEFT_E_PHASE,  RIGHT_E_PHASE   },
  {INPUT_F_LEFT,    INPUT_F_RIGHT,     F_RETURN  ,OUTPUT_F_LEFT,        OUTPUT_F_RIGHT,    LEFT_F_PHASE,  RIGHT_F_PHASE   },
  {INPUT_G_LEFT,    INPUT_G_RIGHT,     G_RETURN  ,OUTPUT_G_LEFT,        OUTPUT_G_RIGHT,    LEFT_G_PHASE,  RIGHT_G_PHASE   },
  {INPUT_MAIN_LEFT, INPUT_MAIN_RIGHT,   "null"   ,OUTPUT_MAIN_LEFT,     OUTPUT_MAIN_RIGHT,    "null"   ,     "null"       } };

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

 void sendEndCommand(){
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
 }

 const String LOOP_TO_OUTPUT = "IN_LOOP_POS";