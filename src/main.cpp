#include <Arduino.h>
#include "MatrixLibrary.h"
#include <EasyRotaryMCP.h>
#include <PCF8574.h>


//--------------------------Device Config-------------------
const String device = "PedalSwitcher";

//---------For Mapping to Nextion Display -----------

//A
const String INPUT_A_LEFT = "A_L_VOL_IN";
const String INPUT_A_RIGHT = "A_R_VOL_IN";
const String OUTPUT_A_LEFT = "A_L_VOL_OUT";
const String OUTPUT_A_RIGHT = "A_R_VOL_OUT";
const String LEFT_A_PHASE = "A_L_PHASE";
const String RIGHT_A_PHASE = "A_R_PHASE";

//B
const String INPUT_B_LEFT = "B_L_VOL_IN";
const String INPUT_B_RIGHT = "B_R_VOL_IN";
const String OUTPUT_B_LEFT = "B_L_VOL_OUT";
const String OUTPUT_B_RIGHT = "B_R_VOL_OUT";
const String LEFT_B_PHASE = "B_L_PHASE";
const String RIGHT_B_PHASE = "B_R_PHASE";

//C
const String INPUT_C_LEFT = "C_L_VOL_IN";
const String INPUT_C_RIGHT = "C_R_VOL_IN";
const String OUTPUT_C_LEFT = "C_L_VOL_OUT";
const String OUTPUT_C_RIGHT = "C_R_VOL_OUT";
const String LEFT_C_PHASE = "C_L_PHASE";
const String RIGHT_C_PHASE = "C_R_PHASE";

//D
const String INPUT_D_LEFT = "D_L_VOL_IN";
const String INPUT_D_RIGHT = "D_R_VOL_IN";
const String OUTPUT_D_LEFT = "D_L_VOL_OUT";
const String OUTPUT_D_RIGHT = "D_R_VOL_OUT";
const String LEFT_D_PHASE = "D_L_PHASE";
const String RIGHT_D_PHASE = "D_R_PHASE";

//E
const String INPUT_E_LEFT = "E_L_VOL_IN";
const String INPUT_E_RIGHT = "E_R_VOL_IN";
const String OUTPUT_E_LEFT = "E_L_VOL_OUT";
const String OUTPUT_E_RIGHT = "E_R_VOL_OUT";
const String LEFT_E_PHASE = "E_L_PHASE";
const String RIGHT_E_PHASE = "E_R_PHASE";

//F
const String INPUT_F_LEFT = "F_L_VOL_IN";
const String INPUT_F_RIGHT = "F_R_VOL_IN";
const String OUTPUT_F_LEFT = "F_L_VOL_OUT";
const String OUTPUT_F_RIGHT = "F_R_VOL_OUT";
const String LEFT_F_PHASE = "F_L_PHASE";
const String RIGHT_F_PHASE = "F_R_PHASE";


//G
const String INPUT_G_LEFT = "G_L_VOL_IN";
const String INPUT_G_RIGHT = "G_R_VOL_IN";
const String OUTPUT_G_LEFT = "G_L_VOL_OUT";
const String OUTPUT_G_RIGHT = "G_R_VOL_OUT";
const String LEFT_G_PHASE = "G_L_PHASE";
const String RIGHT_G_PHASE = "G_R_PHASE";


String VOLUME_FOR_DISPLAY[7][6] = {
// LEFT IN VOL(0)  RIGHT IN VOL(1)  LEFT OUT VOL(2)  RIGHT OUT VOL(3)  LEFT PHASE(4)  RIGHT PHASE(5)    
  {INPUT_A_LEFT,   INPUT_A_RIGHT,   OUTPUT_A_LEFT,   OUTPUT_A_RIGHT,   LEFT_A_PHASE,  RIGHT_A_PHASE   },
  {INPUT_B_LEFT,   INPUT_B_RIGHT,   OUTPUT_B_LEFT,   OUTPUT_B_RIGHT,   LEFT_B_PHASE,  RIGHT_B_PHASE   },
  {INPUT_C_LEFT,   INPUT_C_RIGHT,   OUTPUT_C_LEFT,   OUTPUT_C_RIGHT,   LEFT_C_PHASE,  RIGHT_C_PHASE   },
  {INPUT_D_LEFT,   INPUT_D_RIGHT,   OUTPUT_D_LEFT,   OUTPUT_D_RIGHT,   LEFT_D_PHASE,  RIGHT_D_PHASE   },
  {INPUT_E_LEFT,   INPUT_E_RIGHT,   OUTPUT_E_LEFT,   OUTPUT_E_RIGHT,   LEFT_E_PHASE,  RIGHT_E_PHASE   },
  {INPUT_F_LEFT,   INPUT_F_RIGHT,   OUTPUT_F_LEFT,   OUTPUT_F_RIGHT,   LEFT_F_PHASE,  RIGHT_F_PHASE   },
  {INPUT_G_LEFT,   INPUT_G_RIGHT,   OUTPUT_G_LEFT,   OUTPUT_G_RIGHT,   LEFT_G_PHASE,  RIGHT_G_PHASE  } };

//-----------------------------MATRIX----------------------
AGD2188 matrix; 
//AGD2188 matrix_left = AGD2188(1);

//------------------------------MENU THINGS------------------------------
enum E_MenuState {loops = 1,input = 2,left_output = 3,right_output = 4,NUM_MENU_STATES = 5};
E_MenuState MenuState;
const byte b_end_message = 0xff;

//--------------------------DATA------------------------------ 

int loop_positions[7] = {0,0,0,0,0,0,0};
int volumes[3] = {125,125,125}; // INPUT, OUTPUT_LEFT, OUTPUT_RIGHT;

//------------------Function prototypes------------------------

void updateUI(bool clockwise, int id);
void changeLoopPositions(bool clockwise, int id);
void sendLoopPositions();
void sendEndCommand();
void cycleMenu();
void changeVolume(int id, bool clockwise);

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
  //To Computer
  Serial.begin(115200);
  //To Nextion
  Serial2.begin(9600);

  MenuState = static_cast<E_MenuState>(1);
  Serial.println(device + " booting");

  AGD2188 matrix_left = AGD2188(1);

  //This should eventually not need to happen
  sendLoopPositions();
  sendEndCommand();

  //Not sure yet what this does
	pinMode(pcf21, 0, INPUT_PULLUP);
  pinMode(pcf22, 1, INPUT_PULLUP);

  matrix = AGD2188(); // THis is the default address

  pinMode(ROTARY_INTERUPT_PIN, INPUT_PULLUP);
  pinMode(FOOT_INTERUPT_PIN,INPUT_PULLUP);

  rotary.startup(*updateUI);

  attachInterrupt(digitalPinToInterrupt(ROTARY_INTERUPT_PIN), ROTARY_INTERUPT, FALLING);
  attachInterrupt(digitalPinToInterrupt(FOOT_INTERUPT_PIN),FOOT_INTERUPT,FALLING);

  matrix.wipe_chip();
  
}



void loop() {
  //THIS IS A MESS
    myData = rotary.checkInterrupt(); //  if interupt occured calls UpdateUI()
    if (rotary_flag)
      {
        rotary_flag = false;
        int x = pcf21.read();
        Serial.print("READ Knobs:\t");
        Serial.println(x, HEX);
        if(x == 0xFF){
          cycleMenu();
        }
      }
}

void updateUI(bool clockwise, int id){

  if(MenuState == E_MenuState::loops){
   changeLoopPositions(clockwise, id);
   sendLoopPositions();
   matrix.ArrayToWrite(loop_positions,7);
  }
  if(MenuState == E_MenuState::input){
    changeVolume(id,clockwise);
  }

   }
 
 void changeLoopPositions(bool clockwise, int id){
   int loopArrayPosition = id-1;
   int loopArrayValue = loop_positions[loopArrayPosition];
   if(loopArrayPosition!=7){
   if(clockwise){
      loopArrayValue==7 ? loop_positions[loopArrayPosition] = 0 : loop_positions[loopArrayPosition]++;
   } else {
      loopArrayValue==0 ? loop_positions[loopArrayPosition] = 7 : loop_positions[loopArrayPosition]--;
   }
   
   }
 }

  void sendLoopPositions(){
    for(int i = 0; i < 8; i++){
    Serial2.print("n" + String(i) + ".val=" + String(loop_positions[i]));
    sendEndCommand();
  }
  }


 void sendEndCommand(){
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
 }

void cycleMenu(){
  if(MenuState == 4){
    MenuState = static_cast<E_MenuState>(1);
  } else {
    MenuState = static_cast<E_MenuState>(MenuState+1);
  }

  Serial2.print("page "+String(MenuState));
  sendEndCommand();
}

int volumeForDisplay(int volume){
  return map(volume,0,255,0,100);
}



void changeVolume(int id, bool clockwise){
  if(MenuState == E_MenuState::input){
    Serial.println("Clockwise: " + String(clockwise));
      clockwise ? volumes[0]-- : volumes[0]++;
      volumes[0] = min(volumes[0],255);
      volumes[0] = max(volumes[0],0);
      Serial2.print("j0.val="+String(volumeForDisplay(volumes[0])));
      sendEndCommand();
      Serial2.print("j1.val="+String(volumeForDisplay(volumes[0])));
      sendEndCommand();
      Serial.println(String(volumes[0]));
      Serial.println(volumeForDisplay(volumes[0]));
  }

}




