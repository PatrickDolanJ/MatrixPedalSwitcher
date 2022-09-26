#include <Arduino.h>
#include "MatrixLibrary.h"
#include <EasyRotaryMCP.h>
#include <PCF8574.h>


//--------------------------Device Config-------------------
const String device = "PedalSwitcher";

//---------For Mapping to Nextion Display -----------

//ONE
const String INPUT_ONE_LEFT = "j0";
const String INPUT_ONE_RIGHT = "j1";
const String OUTPUT_ONE_LEFT = "j16";
const String OUTPUT_ONE_RIGHT = "j17";

//TWO
const String INPUT_TWO_LEFT = "j2";
const String INPUT_TWO_RIGHT = "j3";
const String OUTPUT_TWO_LEFT = "j18";
const String OUTPUT_TWO_RIGHT = "j19";

//THREE
const String INPUT_THREE_LEFT = "j4";
const String INPUT_THREE_RIGHT = "j5";
const String OUTPUT_THREE_LEFT = "j20";
const String OUTPUT_THREE_RIGHT = "j21";

//FOUR
const String INPUT_FOUR_LEFT = "j6";
const String INPUT_FOUR_RIGHT = "j7";
const String OUTPUT_FOUR_LEFT = "j22";
const String OUTPUT_FOUR_RIGHT = "j23";

//FIVE
const String INPUT_FIVE_LEFT = "j8";
const String INPUT_FIVE_RIGHT = "j9";
const String OUTPUT_FIVE_LEFT = "j24";
const String OUTPUT_FIVE_RIGHT = "j25";

//SIX
const String INPUT_SIX_LEFT = "j10";
const String INPUT_SIX_RIGHT = "j11";
const String OUTPUT_SIX_LEFT = "j26";
const String OUTPUT_SIX_RIGHT = "j27";


//SEVEN
const String INPUT_SEVEN_LEFT = "j12";
const String INPUT_SEVEN_RIGHT = "j13";
const String OUTPUT_SEVEN_LEFT = "j28";
const String OUTPUT_SEVEN_RIGHT = "j29";

String VOLUME_FOR_DISPLAY[7][4] = {
  {INPUT_ONE_LEFT,   INPUT_ONE_RIGHT,   OUTPUT_ONE_LEFT,   OUTPUT_ONE_RIGHT},
  {INPUT_TWO_LEFT,   INPUT_TWO_RIGHT,   OUTPUT_TWO_LEFT,   OUTPUT_TWO_RIGHT},
  {INPUT_THREE_LEFT, INPUT_THREE_RIGHT, OUTPUT_THREE_LEFT, OUTPUT_THREE_RIGHT},
  {INPUT_FOUR_LEFT,  INPUT_FOUR_RIGHT,  OUTPUT_FOUR_LEFT,  OUTPUT_FOUR_RIGHT},
  {INPUT_FIVE_LEFT,  INPUT_FIVE_RIGHT,  OUTPUT_FIVE_LEFT,  OUTPUT_FIVE_RIGHT},
  {INPUT_SIX_LEFT,   INPUT_SIX_RIGHT,   OUTPUT_SIX_LEFT,   OUTPUT_SIX_RIGHT},
  {INPUT_SEVEN_LEFT, INPUT_SEVEN_RIGHT, OUTPUT_SEVEN_LEFT, OUTPUT_SEVEN_RIGHT}};

//-----------------------------MATRIX----------------------
AGD2188 matrix; // This still needs to interact with both chips!! 


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




