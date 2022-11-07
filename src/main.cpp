#include <Arduino.h>
#include <MatrixLibrary.h>
#include <EasyRotaryMCP.h>
#include <PCF8574.h>
#include <NextionCommands.h>
#include <SPI.h>


//--------------------------Device Config-------------------

const String DEVICE_NAME = "PedalSwitcher";
const int DEFAULT_VOLUME = 125;
const String DEFAULT_COLOR = "19703";
const String HIGHLIGHT_COLOR = "65535"; 
const float LONG_PRESS_INTERVAL_S = 1.75;
const byte ROTARY_ADDRESS = 0x21;
const byte FOOTSWITCH_ADDRESS = 0x22;
const int ROTARY_INTERUPT_PIN = 3; 
const int FOOT_INTERUPT_PIN = 18; 
const int RIGHT_MATRIX_ADDRESS = 0;
const int LEFT_MATRIX_ADDRESS = 4;
const int ROTARY_ENCODER_INTERUPT_PIN = 2;

//-------------For Digital Pots----------------
const int spiDelay = 1;

const int cs0_pin = 32; // 1
const int cs1_pin = 33; // 2
const int cs2_pin = 34; // 3
const int cs3_pin = 35; // 4
const int cs4_pin = 36; // 5
const int cs5_pin = 37; // 6

//-----------------------------MATRIX----------------------------
AGD2188 MatrixRight(RIGHT_MATRIX_ADDRESS); 
AGD2188 MatrixLeft(LEFT_MATRIX_ADDRESS);

//------------------------------MENU------------------------------
enum E_MenuState {loops = 1,input = 2, left_output = 3,right_output = 4, phase = 5, NUM_MENU_OPTIONS=6};
E_MenuState MenuState;
unsigned long PreviousMillis = 0;
unsigned long CurrentTime = 0;
int PreviousRotaryButtonValue;
int FirstFootButtonValue = 0;
int SecondFootButtonValue = 0;

//------------------------------DATA------------------------------ 
int cur_loop_positions[7] = {0,0,0,0,0,0,0};
int cur_input_volumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int cur_left_output_volumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int cur_right_output_volumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int cur_phase[8] = {0,0,0,0,0,0,0,0};
bool cur_return[8] = {1,1,1,1,1,1,1,1};

//----------------------Function prototypes------------------------
void updateUI(bool isClockwise, int id);
void changeLoopPositions(bool isClockwise, int id);
void sendLoopPositions();
void sendEndCommand();
void cycleMenu();
void changeVolume(int id, bool isClockwise, int volume_array[]);
void changePhase(int id, bool isClockwise);
void highlightMenu(bool shouldHighlight);
void changeReturn(int id);
void startCounter();
bool checkPress(int durationInSeconds, int id);
int hexToId(byte hexVal);
void sendReturn(int arrayId);
void initializeDisplay();
void doButton();
void doFoot();
void setVolumesDefault();

//----------------------------Buttons/RotaryEncoders---------------------------
EasyRotary RotaryEncoders(ROTARY_ENCODER_INTERUPT_PIN); //for reading rotary encoder data **NOT BUTTONS**
RotaryData RotaryDataStuct; // struct for holding rotary encoder data
PCF8574 pcf21(ROTARY_ADDRESS); // rotary encoder **BUTTONS**
PCF8574 pcf22(FOOTSWITCH_ADDRESS); // foot switch buttons
volatile bool RotaryFlag = false;
volatile bool FootFlag = false;
//Interupts
void ROTARY_INTERUPT()
{
  RotaryFlag = true;
}

void FOOT_INTERUPT(){
  FootFlag = true;
}
//------------------------------Start------------------------------

void setup() {
  Serial.begin(115200);  //To Computer
  Serial2.begin(9600);  //To Nextion
  Serial.println(DEVICE_NAME + " booting");

  initializeDisplay();
  setVolumesDefault();

	pinMode(pcf21, 0, INPUT_PULLUP);
  pinMode(pcf22, 1, INPUT_PULLUP);
  
  pinMode(ROTARY_INTERUPT_PIN, INPUT_PULLUP);
  pinMode(FOOT_INTERUPT_PIN,INPUT_PULLUP);

  RotaryEncoders.startup(*updateUI); //  if interupt occured calls UpdateUI()

  attachInterrupt(digitalPinToInterrupt(ROTARY_INTERUPT_PIN), ROTARY_INTERUPT, FALLING);
  attachInterrupt(digitalPinToInterrupt(FOOT_INTERUPT_PIN),FOOT_INTERUPT,FALLING);

  pinMode(cs0_pin, OUTPUT);
  pinMode(cs1_pin, OUTPUT);
  pinMode(cs2_pin, OUTPUT);
  pinMode(cs3_pin, OUTPUT);
  pinMode(cs4_pin, OUTPUT);
  pinMode(cs5_pin, OUTPUT);

  SPI.begin();

  MatrixRight.wipeChip();
  MatrixLeft.wipeChip();

  MatrixRight.writeArray(cur_loop_positions,7);
  MatrixLeft.writeArray(cur_loop_positions,7);
  
  
}
//-----------------------------------LOOP-------------------------------------
void loop() {
    RotaryDataStuct = RotaryEncoders.checkInterrupt(); 
    if (RotaryFlag)
      {
      doButton();
      }
    if (FootFlag)
      {
      doFoot();  
      }
    //  MatrixRight.writeData(true, 7, 1);
    //  MatrixRight.readData(8);
    //  delay(3000);
    //  MatrixRight.writeData(false, 7, 1);
    //  MatrixRight.readData(8);
    //  delay(3000);
}
//-----------------------------------------------------------------------------

void updateUI(bool isClockwise, int id){
  
  switch (MenuState){
    case (E_MenuState::loops):
      if(id!=8){
        changeLoopPositions(isClockwise, id);
        sendLoopPositions();
        MatrixRight.writeArray(cur_loop_positions,7);
        MatrixLeft.writeArray(cur_loop_positions,7);
        }
      break;

    case(E_MenuState::input):
      changeVolume(id, isClockwise, cur_input_volumes);
      break;

    case(E_MenuState::left_output):
      changeVolume(id, isClockwise, cur_left_output_volumes);
      break;
    
    case(E_MenuState::right_output):
      changeVolume(id, isClockwise, cur_right_output_volumes);
      break;
    
    case(E_MenuState::phase):
      if(id!=8){
        changePhase(id, isClockwise);
      }
      break;
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
  highlightMenu(false);
  if(MenuState == NUM_MENU_OPTIONS-1){
    MenuState = static_cast<E_MenuState>(1);
  } else {
    MenuState = static_cast<E_MenuState>(MenuState+1);
  }
  Serial.println("MenuState = " + String(MenuState));
  highlightMenu(true);
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
    isClockwise ? volume[idToArray]++ : volume[idToArray]--;
    capVolume(volume, idToArray);
    int volumeForDisplay = volumeToDisplay(volume[idToArray]);
    sendVolumeToDisplay(idToArray, volumeForDisplay); 
}

void sendPhase(int arrayId){
  String left_phase = "";
  String right_phase = "";
  int phase = cur_phase[arrayId];

  if(phase == 0){
    left_phase = PHASES_FOR_DISPLAY[arrayId][0];
    right_phase = PHASES_FOR_DISPLAY[arrayId][0];
  } else if (phase == 1){
    left_phase = PHASES_FOR_DISPLAY[arrayId][0];
    right_phase = PHASES_FOR_DISPLAY[arrayId][1];
  } else if (phase == 2){
    left_phase = PHASES_FOR_DISPLAY[arrayId][1];
    right_phase = PHASES_FOR_DISPLAY[arrayId][0];
  }
  else if (phase == 3){
    left_phase = PHASES_FOR_DISPLAY[arrayId][1];
    right_phase = PHASES_FOR_DISPLAY[arrayId][1];
  }

    Serial2.print(ADDRESS_FOR_DISPLAY[arrayId][5] + ".txt=" + '"' + left_phase + '"');
    sendEndCommand();
    Serial2.print(ADDRESS_FOR_DISPLAY[arrayId][6] + ".txt=" + '"' + right_phase + '"');
    sendEndCommand();
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
 sendPhase(idToArray);
}

void sendReturn(int arrayId){
    String returnToDisplay = cur_return[arrayId] ? STEREO : MONO;
    Serial2.print(ADDRESS_FOR_DISPLAY[arrayId][2] + ".txt=" + '"' + returnToDisplay + '"');
    sendEndCommand();
    Serial.println(ADDRESS_FOR_DISPLAY[arrayId][2] + ".txt=" + '"' + returnToDisplay + '"');
}

void changeReturn(int id){
  int idToArray = id -1;
  if(idToArray!=7){
    cur_return[idToArray] = !cur_return[idToArray];
    sendReturn(idToArray);
  }
}

void highlightMenu(bool shouldHighlightOR){
  String color;
  color = shouldHighlightOR ? HIGHLIGHT_COLOR : DEFAULT_COLOR;
  
  switch (MenuState){
    case (E_MenuState::loops):
      for(int i = 0; i < 8; i++){
        Serial2.print(LOOPS_FOR_DISPLAY[i] + ".pco=" + color);
        sendEndCommand();
      }
      break;

    case(E_MenuState::input):
      for(int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][0] + ".pco=" + color);
        sendEndCommand();
        Serial2.print(ADDRESS_FOR_DISPLAY[i][1] + ".pco=" + color);
        sendEndCommand();
      }
      break;

    case(E_MenuState::left_output):
      for (int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][3] + ".pco=" + color);
        sendEndCommand();
      }
      break;
    
    case(E_MenuState::right_output):
      for (int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][4] + ".pco=" + color);
        sendEndCommand();
      }
      break;
    
    case(E_MenuState::phase):
      for (int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][5] + ".pco=" + color);
        sendEndCommand();
      }
      for (int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][6] + ".pco=" + color);
        sendEndCommand();
      }
      break;
    }
}

void startCounter(){
PreviousMillis = millis();
}


bool checkPress(int durationInSeconds, int id){
  long interval = durationInSeconds * 1000;
  unsigned long CurrentTime = millis();
  long intervalActual = CurrentTime - PreviousMillis;
  bool isLongPress = intervalActual >= interval;
  return (isLongPress);
  } 

  int hexToId(byte hexVal){
    int id = 8;
    switch (hexVal){

      case (0xFE):
        id = 1;
        break;
      case (0xFD):
        id = 2;
        break;
      case (0xFB):
        id = 3;
        break;
      case (0xF7):
        id = 4;
        break;
      case (0xEF):
        id = 5;
        break;
      case (0xDF):
        id = 6;
        break;
      case (0xBF):
        id = 7;
        break;
    }
    return id;
  }
  

void initializeDisplay(){
  //Phases
  for(int i = 0; i <7; i++){
      sendPhase(i);
  }
  //Loops
    sendLoopPositions();
    sendEndCommand();
    MenuState = E_MenuState::input;
  //Input Volumes
  for(int i = 0; i <8; i++){
    sendVolumeToDisplay(i, volumeToDisplay(cur_input_volumes[i])); 
  }
  //Return
  for(int i = 0; i<7; i++){
    sendReturn(i);
  }
  //Left Output
  MenuState = E_MenuState::left_output;
  for(int i = 0; i <8; i++){
    sendVolumeToDisplay(i, volumeToDisplay(cur_left_output_volumes[i])); 
  }
  //Right Output
  MenuState = E_MenuState::right_output;
  for(int i = 0; i <8; i++){
    sendVolumeToDisplay(i, volumeToDisplay(cur_right_output_volumes[i])); 
  }
  //Unhighlight
  for(int i = 1; i <6; i++){
    MenuState = static_cast<E_MenuState>(i);
    highlightMenu(false);
  }
  //Highlight Loops First and set MenuState
  MenuState = E_MenuState::loops;
  highlightMenu(true); 
}

void doButton(){
    RotaryFlag = false;
        int RotaryButtonValue = pcf21.read();
        if(RotaryButtonValue!=0xFF && RotaryButtonValue!=PreviousRotaryButtonValue){
          startCounter();
        }
        Serial.print("READ Knobs:\t");
        Serial.println(RotaryButtonValue, HEX);
        if(RotaryButtonValue == 0xFF && RotaryButtonValue!=PreviousRotaryButtonValue){
          int id = hexToId(PreviousRotaryButtonValue);
          checkPress(LONG_PRESS_INTERVAL_S,id) ? changeReturn(id) : cycleMenu();
        }
          PreviousRotaryButtonValue = RotaryButtonValue;
}

void doFoot(){   
        FootFlag = false;
        int y = pcf22.read();
        Serial.println("Read Foot: " + String(y, HEX));
        if(y!= 0xFF && FirstFootButtonValue!=0){
          FirstFootButtonValue = y;
        }

        if(y!= 0xFF && FirstFootButtonValue != 0 && SecondFootButtonValue !=0){
          SecondFootButtonValue = y;
        }
        // when 2 are pressed and when released sends original hex again aka the other one pressed

        if(y == 0xFF){
          y = 0;
          Serial.println("First Button: " + String(FirstFootButtonValue) + " Second Button: " + String(SecondFootButtonValue));
          FirstFootButtonValue = 0;
          FirstFootButtonValue = 0;
        }
}


void digitalPotWrite(int pot, int value){
  if(pot <= 5){
    digitalWrite(cs0_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs0_pin, HIGH);
  }
  if(pot >= 6 || pot <= 11){
    digitalWrite(cs1_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 6);   
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs1_pin, HIGH);
  }
  if(pot >= 12 || pot <= 17){
    digitalWrite(cs2_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 12);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs2_pin, HIGH);
  }
  if(pot >= 18 || pot <= 23){
    digitalWrite(cs3_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 18);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs3_pin, HIGH);
  }
  if(pot >= 24 || pot <= 29){
    digitalWrite(cs4_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 24);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs4_pin, HIGH);
  }
  if(pot >= 30 || pot <= 35){
    digitalWrite(cs5_pin, LOW);
    delayMicroseconds(spiDelay);
    SPI.transfer(pot - 30);
    SPI.transfer(value);
    delayMicroseconds(spiDelay);
    digitalWrite(cs5_pin, HIGH);
  }
}

void setVolumesDefault(){

pinMode(cs0_pin, OUTPUT);
pinMode(cs1_pin, OUTPUT);
pinMode(cs2_pin, OUTPUT);
pinMode(cs3_pin, OUTPUT);
pinMode(cs4_pin, OUTPUT);
pinMode(cs5_pin, OUTPUT);
// initialize SPI:
SPI.begin();

for(int i = 0; i<36; i++){
  digitalPotWrite(i, 255);//pot, level
  Serial.print(i);
  Serial.println("on");
}
}



