#include <Arduino.h>
#include "MatrixLibrary.h"
#include <EasyRotaryMCP.h>
#include <PCF8574.h>


AGD2188 matrix;
bool wipe_chip_once = true;
byte testByte = 0;
int test_array[8] {3,1,0,0,0,1,0,0}; // expected outcome should be to connect x7 to y1 and y5, then connect x1 and x5 to y0, then x0 to y7;
int menuState = 1;
const byte b_end_message = 0xff;

//Loop Positions 
int i_loop[8] = {0,0,0,0,0,0,0,0};
//

bool state;

//Function prototypes
void updateUI(bool clockwise, int id);
void sendLoopPositions(bool clockwise, int id);
void sendEndCommand();
void cycleMenu();
//


EasyRotary rotary;
RotaryData myData;

//For Rotary Buttons
PCF8574 pcf21(0x21);
PCF8574 pcf22(0x22);
const int IRQPIN = 3;
volatile bool flag = false;
void pcf_irq()
{
  flag = true;
}
//

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial.println("From setup");
  Serial1.print("page 1");
  sendEndCommand();

  matrix = AGD2188();

  pcf21.begin();
  pcf22.begin();
  pinMode(IRQPIN, INPUT_PULLUP);
  rotary.startup(*updateUI);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), pcf_irq, FALLING);
  pcf21.read8();
}

void loop() {
   if(wipe_chip_once)
   {
   matrix.wipe_chip();
   wipe_chip_once = false;
   matrix.ArrayToWrite(test_array,8);
   }
    myData = rotary.checkInterrupt();
    if (flag)
      {
        flag = false;
        int x = pcf21.read8();
        //int y = pcf22.read8();
        Serial.print("READ Knobs:\t");
        Serial.println(x, HEX);
        // Serial.print("READ Foots:\t");
        // Serial.println(y, HEX);
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
   
   
   Serial1.print("n" + String(loopArrayPosition) + ".val="+String(i_loop[loopArrayPosition]));
   sendEndCommand();
   }
 }

 void sendEndCommand(){
   Serial1.write(b_end_message);
   Serial1.write(b_end_message);
   Serial1.write(b_end_message);
 }

void cycleMenu(){
  
  if(menuState == 4){
    menuState = 1;
  } else {
    menuState++;
  }
  Serial1.print("page "+String(menuState));
  sendEndCommand();
}


