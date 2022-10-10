#include <Arduino.h>
#include "MatrixLibrary.h"
#include <EasyRotaryMCP.h>
#include <PCF8574.h>


//--------------------------Device Config-------------------
const String DEVICE = "PedalSwitcher";
const int DEFAULT_VOLUME = 125;
const String DEFAULT_COLOR = "19703";
const String HIGHLIGHT_COLOR = "62025"; 

//---------For Nextion Display -----------
const byte b_end_message = 0xff;
const String STEREO = "S";
const String MONO = "M";

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
// There are some places in the code that need to change if this changes BE AWARE!!
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

//-----------------------------MATRIX----------------------
AGD2188 matrix_right; 
AGD2188 matrix_left;

//------------------------------MENU THINGS------------------------------
enum E_MenuState {loops = 1,input = 2, return_m = 3, left_output = 4,right_output = 5, phase = 6};
E_MenuState MenuState;
const int NUM_MENU_OPTIONS = 6;

//--------------------------DATA------------------------------ 
int cur_loop_positions[7] = {0,0,0,0,0,0,0};
int cur_input_volumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int cur_left_output_volumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int cur_right_output_volumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int cur_phase[8] = {0,0,0,0,0,0,0,0};
bool cur_return[8] = {1,1,1,1,1,1,1,1};
//------------------Function prototypes------------------------

void updateUI(bool isClockwise, int id);
void changeLoopPositions(bool isClockwise, int id);
void sendLoopPositions();
void sendEndCommand();
void cycleMenu();
void changeVolume(int id, bool isClockwise, int volume_array[]);
void changePhase(int id, bool isClockwise);
void highlightMenu(bool shouldHighlight);
void changeReturn(int id);

//--------------------For Rotary Buttons------------------------

EasyRotary rotary; //for reading rotary encoder data
RotaryData myData; // struct for holding rotary encoder data
PCF8574 pcf21(0x21); // rotary encoder buttons
PCF8574 pcf22(0x22); // foot switch buttons
const int ROTARY_INTERUPT_PIN = 3; //Rotary Push Buttons
const int FOOT_INTERUPT_PIN = 18; // For the Foot Switches
volatile bool rotary_flag = false;
volatile bool foot_flag = false;
//Interupts
void ROTARY_INTERUPT()
{
  rotary_flag = true;
}

void FOOT_INTERUPT(){
  foot_flag = true;
}
////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);  //To Computer
  Serial2.begin(9600);  //To Nextion
  Serial.println(DEVICE + " booting");
  MenuState = static_cast<E_MenuState>(1);

  sendLoopPositions();
  sendEndCommand();
  //highlightMenu(true);

	pinMode(pcf21, 0, INPUT_PULLUP);
  pinMode(pcf22, 1, INPUT_PULLUP);

  matrix_right = AGD2188(); // This is the default address
  //matrix_left = AGD2188(1);

  pinMode(ROTARY_INTERUPT_PIN, INPUT_PULLUP);
  pinMode(FOOT_INTERUPT_PIN,INPUT_PULLUP);

  rotary.startup(*updateUI);

  attachInterrupt(digitalPinToInterrupt(ROTARY_INTERUPT_PIN), ROTARY_INTERUPT, FALLING);
  attachInterrupt(digitalPinToInterrupt(FOOT_INTERUPT_PIN),FOOT_INTERUPT,FALLING);

  matrix_right.wipe_chip();
  
  
}
/////////////////////////////////// LOOP /////////////////////////////////////////
void loop() {
    myData = rotary.checkInterrupt(); //  if interupt occured calls UpdateUI()
    if (rotary_flag)
      {
        rotary_flag = false;
        int x = pcf21.read();
        Serial.print("READ Knobs:\t");
        Serial.println(x, HEX);
        if(x == 0xFF){
          highlightMenu(false);
          cycleMenu();
          highlightMenu(true);
        }
      }
}
///////////////////////////////////////////////////////////////////////////////////

void updateUI(bool isClockwise, int id){
  //LOOPS
  if(MenuState == E_MenuState::loops && id!=8){
   changeLoopPositions(isClockwise, id);
   sendLoopPositions();
   matrix_right.ArrayToWrite(cur_loop_positions,7);
  }
  //INPUT
  else if(MenuState == E_MenuState::input ){
    changeVolume(id, isClockwise, cur_input_volumes);
  }
  //RETURN
  else if(MenuState == E_MenuState::return_m && id!=8){
    changeReturn(id);
  }
  //LEFT OUTPUT VOL
  else if(MenuState == E_MenuState::left_output){
    changeVolume(id, isClockwise, cur_left_output_volumes);
  }
  // RIGHT OUTPUT VOL
  else if(MenuState == E_MenuState::right_output){
    changeVolume(id, isClockwise, cur_right_output_volumes);
  }
  //PHASE
  else if(MenuState == E_MenuState::phase && id!=8){
    changePhase(id, isClockwise);
  }
   }
 
 void changeLoopPositions(bool isClockwise, int id){
   int loopArrayPosition = id-1;
   int loopArrayValue = cur_loop_positions[loopArrayPosition];
   if(loopArrayPosition!=7){
   if(isClockwise){
      loopArrayValue==7 ? cur_loop_positions[loopArrayPosition] = 0 : cur_loop_positions[loopArrayPosition]++;
   } else {
      loopArrayValue==0 ? cur_loop_positions[loopArrayPosition] = 7 : cur_loop_positions[loopArrayPosition]--;
   }
   }
 }

  void sendLoopPositions(){
    for(int i = 0; i < 8; i++){
    Serial2.print(LOOPS_FOR_DISPLAY[i] + ".val=" + String(cur_loop_positions[i]));
    sendEndCommand();
  }
  }


 void sendEndCommand(){
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
 }

void cycleMenu(){
  if(MenuState == NUM_MENU_OPTIONS){
    MenuState = static_cast<E_MenuState>(1);
  } else {
    MenuState = static_cast<E_MenuState>(MenuState+1);
  }
  Serial.println("MenuState = " + String(MenuState));
}

int volumeToDisplay(int volume){
  return map(volume,0,255,0,100);
}

void capVolume(int volume[], int arrayPosition){
  volume[arrayPosition] = min(volume[arrayPosition],255);
  volume[arrayPosition] = max(volume[arrayPosition],0);
} 

void sendVolumeToDisplay(int idForArray, int volumeForDisplay){ 
  if (MenuState == E_MenuState::input){
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][0] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][1] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
  } else if(MenuState == E_MenuState::left_output){
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][3] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
  } else if(MenuState == E_MenuState::right_output){
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][4] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
  }
}

void changeVolume(int id, bool isClockwise, int volume[]){
    int idToArray = id -1;
    isClockwise ? volume[idToArray]-- : volume[idToArray]++;
    capVolume(volume, idToArray);
    int volumeForDisplay = volumeToDisplay(volume[idToArray]);
    sendVolumeToDisplay(idToArray, volumeForDisplay); 
}

void changePhase(int id, bool isClockwise){

  int idToArray = id -1;
  if(isClockwise){
    if(cur_phase[idToArray] == 3){
      cur_phase[idToArray] = 0;
    } else {
      cur_phase[idToArray]++;
    }
  } else {
    if(cur_phase[idToArray]==0){
      cur_phase[idToArray] = 3;
    } else {
      cur_phase[idToArray]--;
    }
  }

  String left_phase = "";
  String right_phase = "";
  int phase = cur_phase[idToArray];

  if(phase == 0){
    left_phase = PHASES_FOR_DISPLAY[idToArray][0];
    right_phase = PHASES_FOR_DISPLAY[idToArray][0];
  } else if (phase == 1){
    left_phase = PHASES_FOR_DISPLAY[idToArray][0];
    right_phase = PHASES_FOR_DISPLAY[idToArray][1];
  } else if (phase == 2){
    left_phase = PHASES_FOR_DISPLAY[idToArray][1];
    right_phase = PHASES_FOR_DISPLAY[idToArray][0];
  }
  else if (phase == 3){
    left_phase = PHASES_FOR_DISPLAY[idToArray][1];
    right_phase = PHASES_FOR_DISPLAY[idToArray][1];
  }
    // The Columns of the two phases (5,6)
    //currently not working, although the color seems changeable, not sure whats up 
    Serial2.print(ADDRESS_FOR_DISPLAY[idToArray][5] + ".txt=" + '"' + left_phase + '"');
    sendEndCommand();
    Serial2.print(ADDRESS_FOR_DISPLAY[idToArray][6] + ".txt=" + '"' + right_phase + '"');
    sendEndCommand();

}

void changeReturn(int id){
  int idToArray = id -1;
  cur_return[idToArray] = !cur_return[idToArray];
  String returnToDisplay = cur_return[idToArray] ? STEREO : MONO;
  Serial2.print(ADDRESS_FOR_DISPLAY[idToArray][2] + ".txt=" + '"' + returnToDisplay + '"');
  sendEndCommand();
}

void highlightMenu(bool shouldHighlightOR){
  String color;
  color = shouldHighlightOR ? HIGHLIGHT_COLOR : DEFAULT_COLOR;

  if(MenuState == E_MenuState::loops){
    for(int i = 0; i < 8; i++){
      Serial2.print(LOOPS_FOR_DISPLAY[i] + ".pco=" + color);
      sendEndCommand();
    }
  } else if(MenuState == E_MenuState::input){
    for(int i = 0; i <8; i++){
      Serial2.print(ADDRESS_FOR_DISPLAY[i][0] + ".pco=" + color);
      sendEndCommand();
      Serial2.print(ADDRESS_FOR_DISPLAY[i][1] + ".pco=" + color);
      sendEndCommand();
    }
  } else if (MenuState == E_MenuState::return_m){
    for (int i = 0; i <8; i++){
      Serial2.print(ADDRESS_FOR_DISPLAY[i][2] + ".pco=" + color);
      sendEndCommand();
    }
  } else if (MenuState == E_MenuState::left_output){
    for (int i = 0; i <8; i++){
      Serial2.print(ADDRESS_FOR_DISPLAY[i][3] + ".pco=" + color);
      sendEndCommand();
    }
  } else if (MenuState == E_MenuState::right_output){
    for (int i = 0; i <8; i++){
      Serial2.print(ADDRESS_FOR_DISPLAY[i][4] + ".pco=" + color);
      sendEndCommand();
    }
  } else if (MenuState == E_MenuState::phase){
    for (int i = 0; i <8; i++){
      Serial2.print(ADDRESS_FOR_DISPLAY[i][5] + ".pco=" + color);
      sendEndCommand();
    }
    for (int i = 0; i <8; i++){
      Serial2.print(ADDRESS_FOR_DISPLAY[i][6] + ".pco=" + color);
      sendEndCommand();
    }
  }
}





