#include <Arduino.h>
#include "MatrixLibrary.h"
#include <EasyRotaryMCP.h>
#include <PCF8574.h>

const String device = "PedalSwitcher";
AGD2188 matrix; // This still needs to interact with both chips!! 
EasyRotary rotary;
RotaryData myData;
int test_array[8] {3,1,0,0,0,1,0,0}; // expected outcome should be to connect x7 to y1 and y5, then connect x1 and x5 to y0, then x0 to y7;
int menuState = 1;
const byte b_end_message = 0xff;

//Loop Positions 
int i_loop[8] = {0,0,0,0,0,0,0,0};

//Function prototypes
void updateUI(bool clockwise, int id);
void sendLoopPositions(bool clockwise, int id);
void sendEndCommand();
void cycleMenu();

//For Rotary Buttons
PCF8574 pcf21(0x21);
PCF8574 pcf22(0x22);
const int ROTARY_INTERUPT_PIN = 3; //Rotary Push Buttons
const int FOOT_INTERUPT_PIN = 18; // For the Foot Switches
volatile bool rotary_flag = false;
volatile bool foot_flag = false;

void ROTARY_INTERUPT()
{
  rotary_flag = true;
}

void FOOT_INTERUPT(){
  foot_flag = true;
}
//

void setup() {
  //To Computer
  Serial.begin(115200);
  //To Nextion
  Serial2.begin(9600);

  Serial.println(device + " booting");

  //This should eventually not need to happen
  Serial2.print("page 1");
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
  matrix.ArrayToWrite(test_array,8);
  matrix.wipe_chip();

}

void loop() {
  //THIS IS A MESS
    myData = rotary.checkInterrupt();
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
   sendLoopPositions(clockwise, id);
   }
 
 void sendLoopPositions(bool clockwise, int id){
   int loopArrayPosition = id-1;
   int loopArrayValue = i_loop[loopArrayPosition];
   if(loopArrayPosition!=7){
   if(clockwise){
      loopArrayValue==7 ? i_loop[loopArrayPosition] = 0 : i_loop[loopArrayPosition]++;
   } else {
      loopArrayValue==0 ? i_loop[loopArrayPosition] = 7 : i_loop[loopArrayPosition]--;
   }
   
   
   Serial2.print("n" + String(loopArrayPosition) + ".val="+String(i_loop[loopArrayPosition]));
   sendEndCommand();
   }
 }

 void sendEndCommand(){
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
   Serial2.write(b_end_message);
 }

void cycleMenu(){
  
  if(menuState == 4){
    menuState = 1;
  } else {
    menuState++;
  }
  Serial2.print("page "+String(menuState));
  sendEndCommand();
}


