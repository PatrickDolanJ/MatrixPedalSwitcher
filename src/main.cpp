#include <common.h>
#include <Arduino.h>

//-----------------------------MATRIX----------------------------
AGD2188 MatrixRight(RIGHT_MATRIX_ADDRESS); 
AGD2188 MatrixLeft(LEFT_MATRIX_ADDRESS);

//------------------------------MENU------------------------------
enum E_MenuState {LOOPS = 1,INPUT_VOLUMES = 2, LEFT_OUTPUT_VOLUMES = 3,RIGHT_OUTPUT_VOLUMES = 4, PHASE = 5, NUM_MENU_OPTIONS = 6};
E_MenuState MenuState;
unsigned long LongPressPreviousMIllis = 0;
unsigned long CurrentTime = 0;
int PreviousRotaryButtonValue = 0xFF;
int PreviousFootValue = -1;
bool TwoFootButtonsPressed = false;
unsigned long DelayTrailsPreviousMillis = 0;

//------------------------------DATA------------------------------
PresetData current,presetA, presetB, presetC, presetD, presetE;
PresetData presets[5] = {presetA,presetB,presetC,presetD,presetE};
//----------------------Function prototypes------------------------

//Menu and Nextion
void updateUI(bool isClockwise, int id);
void cycleMenu(int id);
void highlightMenu(bool shouldHighlight);
void highLightReturn(int id, bool shouldHighlight);
void initializeDisplay();

void sendLoopPositionsNextion();
void sendVolumeToNextion(int idForArray, int volumeForDisplay);
void sendReturnNextion(int id);
void sendPhaseToNextion(int arrayId);

//Data Changes
void changeLoopPositions(bool isClockwise, int id);
void changeVolume(int id, bool isClockwise, int volume_array[]);
void changePhase(int id, bool isClockwise);
void changeReturn(int id);

//Sending Data
void setVolumesDefault();
void sendReturn(int arrayId);
void sendVolumeToDigitalPots(int id);
void changeFootLED(int ledID, bool isOn);
void turnOffAllFootLEDs();
void sendRelay(byte address, int internalPin, int value);
void sendPhaseRelay(int loopID);
void sendReturnRelay(int id, bool onOrOff);
void initializeRelays();


//Internal Functions
void DelayTrailStartCounter();
void LongPressStartCounter();
void doButton();
void doFoot();
bool checkPress(int durationInSeconds);
int footHextoID(byte hex);
void duringLongPress();
void doLongPress(int id);
void copyPreset(PresetData &current, PresetData &newPreset);
void changePreset(int id); //updates Nextion and Sends Data

//----------------------------Buttons/RotaryEncoders---------------------------
EasyRotary RotaryEncoders(ROTARY_ENCODER_INTERUPT_PIN); //for reading rotary encoder data **NOT BUTTONS**
RotaryData RotaryDataStuct; // struct for holding rotary encoder data
PCF8574 rotaryExpander(ROTARY_BUTTONS_ADDRESS); // rotary encoder **BUTTONS**
PCF8574 footExpander(FOOTSWITCH_ADDRESS); // foot switch buttons
volatile bool RotaryFlag = false;
volatile bool FootFlag = false;

//----------------------------------Interupts-----------------------------------
void ROTARY_INTERUPT()
{
  RotaryFlag = true;
}

void FOOT_INTERUPT(){
  FootFlag = true;
}

//------------------------------LEDS------------------------------
PCF8574 ledExpander(FOOT_SWITCH_LIGHTS_ADDRESS);


//---------------------------RELAYS-----------------------

//Normaly Unenergized(0) = Stereo
//Normally Unenergized(0) = in Phase

PCF8574 LeftPhaseRelays(LEFT_PHASE_RELAYS_ADDRESS);
PCF8574 RightPhaseRelays(RIGHT_PHASE_RELAY_ADDRESS);
PCF8574 ReturnRelayExpander(RETURN_RELAYS_ADDRESS);

//------------------------------Setup------------------------------

void setup() {
  Serial.begin(115200);  //To Computer
  Serial2.begin(9600);  //To Nextion
  while(!Serial){};
  Serial.println(DEVICE_NAME + " booting");

  i2CScan();
  SDCard card(SD_CARD_CHIP_SELECT_PIN);

  initializeDisplay();
  initializeRelays();
 
  
	pinMode(rotaryExpander, 0, INPUT_PULLUP);
  pinMode(footExpander, 1, INPUT_PULLUP);
  
  //Setting up Interupts for Foot Switches and 
  pinMode(ROTARY_INTERUPT_PIN, INPUT_PULLUP);
  pinMode(FOOT_INTERUPT_PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROTARY_INTERUPT_PIN), ROTARY_INTERUPT, FALLING);
  attachInterrupt(digitalPinToInterrupt(FOOT_INTERUPT_PIN),FOOT_INTERUPT,FALLING);

  RotaryEncoders.startup(*updateUI); //  if interupt occured calls UpdateUI()


  SPI.begin();
  
  pinMode(cs0_pin, OUTPUT);
  pinMode(cs1_pin, OUTPUT);
  pinMode(cs2_pin, OUTPUT);
  pinMode(cs3_pin, OUTPUT);
  pinMode(cs4_pin, OUTPUT);
  pinMode(cs5_pin, OUTPUT);
  setVolumesDefault();

  presetA.presetID = 0;
  presetB.presetID = 1;
  presetC.presetID = 2;
  presetD.presetID = 3;
  presetE.presetID = 4;

  changePreset(0);

  //This should happen anyway but just in case
  MatrixRight.wipeChip(); 
  MatrixLeft.wipeChip();

  MatrixRight.writeArray(current.loopPositions,7);
  MatrixLeft.writeArray(current.loopPositions,7);
  }

//-----------------------------------LOOP-------------------------------------
void loop() {
  // Check for rotary encoder data
    RotaryDataStuct = RotaryEncoders.checkInterrupt(); 

  // Check for rotary encoder button press
    if (RotaryFlag)
      {
      doButton();
      }
  // Check for foot button press
    if (FootFlag)
      {
      doFoot();  
      }
  // Check for Double Foot Press but not Release
      if(PreviousRotaryButtonValue!=0xFF && checkPress(LONG_PRESS_INTERVAL_S)){
       duringLongPress();
      }
}

//-------------------------------When Rotary Encoder Button is pressed--------------------------
//----------------------------------------------------------------------------------------------
void doButton(){
    RotaryFlag = false;
        int RotaryButtonValue = rotaryExpander.read();
        if(RotaryButtonValue!=0xFF && RotaryButtonValue!=PreviousRotaryButtonValue){
          LongPressStartCounter();
        }

        if(RotaryButtonValue == 0xFF && RotaryButtonValue!=PreviousRotaryButtonValue){
          int id = rotaryHexToId(PreviousRotaryButtonValue);
          checkPress(LONG_PRESS_INTERVAL_S) ? doLongPress(id) : cycleMenu(id);
        }
          PreviousRotaryButtonValue = RotaryButtonValue;
}

//--------------------------------------When Foot Switch is pressed---------------------------------
//--------------------------------------------------------------------------------------------------
void doFoot(){   
        FootFlag = false;
        int footID = footHextoID(footExpander.read());
        // when 2 are pressed and when released sends original hex again aka the other one pressed

        if(footID != PreviousFootValue){
          if(footID == -2){
            TwoFootButtonsPressed = true;
          }
          if(footID == -1){
            if(TwoFootButtonsPressed){
            //DO DOUBLE PRESS
            Serial.println("Two Buttons Pressed");
            TwoFootButtonsPressed = false;
            } else {
            //DO SINGLE PRESS
              Serial.println("One Button Pressed: " + String(PreviousFootValue));
              turnOffAllFootLEDs();
              changeFootLED(PreviousFootValue, true);
              changePreset(PreviousFootValue);
            }
          }
          }
        PreviousFootValue = footID;
}

//---------------------------------------------------------------------------------------------------

//--------------------------------------Long Press=-------------------------------------

void duringLongPress(){
  int idToArray = rotaryHexToId(PreviousRotaryButtonValue)-1;
  highLightReturn(idToArray, true);
}

void doLongPress(int id){
  int idToArray = id-1;
  changeReturn(idToArray);
  sendReturnNextion(idToArray);
  sendReturnRelay(idToArray, current.returns[idToArray]); //CurrentReturns[idToArray]);
}
//---------------------------------------------------------------------------------------------------

//-----------------------------------------Rotary Spin-----------------------------------------------
void updateUI(bool isClockwise, int id){
  
  switch (MenuState){
    case (E_MenuState::LOOPS):
      if(id!=8){
        changeLoopPositions(isClockwise, id);
        sendLoopPositionsNextion();
        MatrixRight.writeArray(current.loopPositions,7);
        MatrixLeft.writeArray(current.loopPositions,7);
        }
      break;

    case(E_MenuState::INPUT_VOLUMES):
      changeVolume(id, isClockwise, current.inputVolumes);       //CurrentInputVolumes);
      break;

    case(E_MenuState::LEFT_OUTPUT_VOLUMES):
      changeVolume(id, isClockwise, current.leftOutputVolumes);  //CurrentLeftOutputVolumes
      break;
    
    case(E_MenuState::RIGHT_OUTPUT_VOLUMES):
      changeVolume(id, isClockwise, current.rightOutputVolumes); //CurrentRightOutputVolumes
      break;
    
    case(E_MenuState::PHASE):
      if(id!=8){
        changePhase(id, isClockwise);
      }
      break;
    }
  }
 //---------------------------------------------------------------------------------------------------

 void changeLoopPositions(bool isClockwise, int id){
   int loopArrayPosition = id-1;
   int loopArrayValue = current.loopPositions[loopArrayPosition];  //CurrentLoopPositions[loopArrayPosition]
   if(loopArrayPosition!=7){
   if(isClockwise){
      loopArrayValue==7 ? current.loopPositions[loopArrayPosition] = 0 : current.loopPositions[loopArrayPosition]++; //CurrentLoopPositions[loopArrayPosition]
   } else {
      loopArrayValue==0 ? current.loopPositions[loopArrayPosition] = 7 : current.loopPositions[loopArrayPosition]--;
   }
   }
 }

  void sendLoopPositionsNextion(){
    for(int i = 0; i < 8; i++){
    Serial2.print(LOOPS_FOR_DISPLAY[i] + ".val=" + String(current.loopPositions[i])); //CurrentLoopPositions[i]
    sendEndCommand();
  }
  }

void cycleMenu(int id){
  if(id ==1){
  highlightMenu(false);
    if(MenuState == NUM_MENU_OPTIONS-1){
      MenuState = static_cast<E_MenuState>(1);
    } else {
      MenuState = static_cast<E_MenuState>(MenuState+1);
    }
      Serial.println("MenuState = " + String(MenuState));
      highlightMenu(true);
  } else if(id ==2)
  {
    highlightMenu(false);
    if(MenuState == 1){
    MenuState = static_cast<E_MenuState>(NUM_MENU_OPTIONS-1);
    } else {
    MenuState = static_cast<E_MenuState>(MenuState-1);
    }
    Serial.println("MenuState = " + String(MenuState));
    highlightMenu(true);
  }
}

int volumeToDisplay(int volume){
  return map(volume,0,255,0,100);
}

void capVolume(int volume[], int arrayPosition){
  volume[arrayPosition] = min(volume[arrayPosition],255);
  volume[arrayPosition] = max(volume[arrayPosition],0);
} 

void sendVolumeToNextion(int idForArray, int volumeForDisplay){ 
  if (MenuState == E_MenuState::INPUT_VOLUMES){
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][0] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][1] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
  } else if(MenuState == E_MenuState::LEFT_OUTPUT_VOLUMES){
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][3] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
  } else if(MenuState == E_MenuState::RIGHT_OUTPUT_VOLUMES){
    Serial2.print(ADDRESS_FOR_DISPLAY[idForArray][4] + ".val=" +String(volumeForDisplay));
    sendEndCommand();
  }
}

void changeVolume(int id, bool isClockwise, int volume[]){
    int idToArray = id -1;
    isClockwise ? volume[idToArray]+=10 : volume[idToArray]-=10;
    capVolume(volume, idToArray);
    int volumeForDisplay = volumeToDisplay(volume[idToArray]);
    sendVolumeToNextion(idToArray, volumeForDisplay); 
    sendVolumeToDigitalPots(idToArray);
}

void sendPhaseToNextion(int arrayId){
  String left_phase = "";
  String right_phase = "";
  int PHASE = current.phase[arrayId]; //CurrentPhase[arrayId] 

  if(PHASE == 0){
    //Both Normal
    left_phase = PHASES_FOR_DISPLAY[arrayId][0]; 
    right_phase = PHASES_FOR_DISPLAY[arrayId][0];
  } else if (PHASE == 1){

    left_phase = PHASES_FOR_DISPLAY[arrayId][0];
    right_phase = PHASES_FOR_DISPLAY[arrayId][1];
  } else if (PHASE == 2){
    left_phase = PHASES_FOR_DISPLAY[arrayId][1];
    right_phase = PHASES_FOR_DISPLAY[arrayId][0];
  }
  else if (PHASE == 3){
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
    if(current.phase[idToArray] == 3){ //CurrentPhase[idToArray]
      current.phase[idToArray] = 0;
    } else {
      current.phase[idToArray]++;
    }
  } else {
    if(current.phase[idToArray]==0){
      current.phase[idToArray] = 3;
    } else {
      current.phase[idToArray]--;
    }
  }
  sendPhaseToNextion(idToArray);
  sendPhaseRelay(idToArray);
}

void sendReturnNextion(int arrayId){
    String returnToDisplay = current.returns[arrayId] ? MONO : STEREO;  //CurrentReturns[arrayId] 
    Serial2.print(ADDRESS_FOR_DISPLAY[arrayId][2] + ".txt=" + '"' + returnToDisplay + '"');
    sendEndCommand();
    highLightReturn(arrayId, false);
}

void changeReturn(int id){
  if(id!=7){
    current.returns[id] = !current.returns[id]; //CurrentReturns[arrayId] 
  }
}

void highlightMenu(bool shouldHighlightOR){
  String color;
  color = shouldHighlightOR ? HIGHLIGHT_COLOR : DEFAULT_COLOR;
  
  switch (MenuState){
    case (E_MenuState::LOOPS):
      for(int i = 0; i < 8; i++){
        Serial2.print(LOOPS_FOR_DISPLAY[i] + ".pco=" + color);
        sendEndCommand();
      }
      break;

    case(E_MenuState::INPUT_VOLUMES):
      for(int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][0] + ".pco=" + color);
        sendEndCommand();
        Serial2.print(ADDRESS_FOR_DISPLAY[i][1] + ".pco=" + color);
        sendEndCommand();
      }
      break;

    case(E_MenuState::LEFT_OUTPUT_VOLUMES):
      for (int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][3] + ".pco=" + color);
        sendEndCommand();
      }
      break;
    
    case(E_MenuState::RIGHT_OUTPUT_VOLUMES):
      for (int i = 0; i <8; i++){
        Serial2.print(ADDRESS_FOR_DISPLAY[i][4] + ".pco=" + color);
        sendEndCommand();
      }
      break;
    
    case(E_MenuState::PHASE):
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

void LongPressStartCounter(){
LongPressPreviousMIllis = millis();
}


bool checkPress(int durationInSeconds){
  long interval = durationInSeconds * 1000;
  unsigned long CurrentTime = millis();
  long intervalActual = CurrentTime - LongPressPreviousMIllis;
  bool isLongPress = intervalActual >= interval;
  return isLongPress;
  } 

  
void initializeDisplay(){
  //Phases
  for(int i = 0; i <7; i++){
      sendPhaseToNextion(i);
  }
  //Loops
    sendLoopPositionsNextion();
    sendEndCommand();
    MenuState = E_MenuState::INPUT_VOLUMES;
  //Input Volumes
  for(int i = 0; i <8; i++){
    sendVolumeToNextion(i, volumeToDisplay(current.inputVolumes[i]));  //CurrentInputVolumes[i]
  }
  //Return
  for(int i = 0; i<7; i++){
    sendReturnNextion(i);
  }
  //Left Output
  MenuState = E_MenuState::LEFT_OUTPUT_VOLUMES;
  for(int i = 0; i <8; i++){
    sendVolumeToNextion(i, volumeToDisplay(current.leftOutputVolumes[i])); //CurrentLeftOutputVolumes[i]
  }
  //Right Output
  MenuState = E_MenuState::RIGHT_OUTPUT_VOLUMES;
  for(int i = 0; i <8; i++){
    sendVolumeToNextion(i, volumeToDisplay(current.rightOutputVolumes[i])); //CurrentRightOutputVolumes[i]
  }
  //Unhighlight
  for(int i = 1; i <6; i++){
    MenuState = static_cast<E_MenuState>(i);
    highlightMenu(false);
  }
  //Highlight Loops First and set MenuState
  MenuState = E_MenuState::LOOPS;
  highlightMenu(true); 

  turnOffAllFootLEDs();
  changeFootLED(0,true);
}




void setVolumesDefault(){
//FOR INPUT VOLUMES
for(int i = 0; i<8; i++){
  digitalPotWrite(potID[LEFT_INPUT_VOLUME_POTS_IDS[1][i]],LEFT_INPUT_VOLUME_POTS_IDS[0][i],DEFAULT_VOLUME);
  digitalPotWrite(potID[RIGHT_INPUT_VOLUME_POTS_IDS[1][i]],RIGHT_INPUT_VOLUME_POTS_IDS[0][i],DEFAULT_VOLUME); 
}

//FOR LEFT OUTPUT
for(int i = 0; i<8; i++){
  digitalPotWrite(potID[LEFT_OUTPUT_VOLUME_POTS_IDS[1][i]],LEFT_OUTPUT_VOLUME_POTS_IDS[0][i],DEFAULT_VOLUME);
}

// FOR RIGHT OUTPUT
for(int i = 0; i<8; i++){
  digitalPotWrite(potID[RIGHT_OUTPUT_VOLUME_POTS_IDS[1][i]],RIGHT_OUTPUT_VOLUME_POTS_IDS[0][i],DEFAULT_VOLUME);
}
}

void sendVolumeToDigitalPots(int id){
  switch(MenuState)
  {
    case(E_MenuState::INPUT_VOLUMES):
      digitalPotWrite(potID[LEFT_INPUT_VOLUME_POTS_IDS[1][id]],LEFT_INPUT_VOLUME_POTS_IDS[0][id],current.inputVolumes[id]); //CurrentInputVolumes[id]
      digitalPotWrite(potID[RIGHT_INPUT_VOLUME_POTS_IDS[1][id]],RIGHT_INPUT_VOLUME_POTS_IDS[0][id],current.inputVolumes[id]);
      break;
  
    case(E_MenuState::LEFT_OUTPUT_VOLUMES):
      digitalPotWrite(potID[LEFT_OUTPUT_VOLUME_POTS_IDS[1][id]],LEFT_OUTPUT_VOLUME_POTS_IDS[0][id],current.leftOutputVolumes[id]); //CurrentLeftOutputVolumes[id]
      break;

    case(E_MenuState::RIGHT_OUTPUT_VOLUMES):
      digitalPotWrite(potID[RIGHT_OUTPUT_VOLUME_POTS_IDS[1][id]],RIGHT_OUTPUT_VOLUME_POTS_IDS[0][id],current.rightOutputVolumes[id]); //CurrentRightOutputVolumes[id]
      break;
  }
}


int footHextoID(byte hex){
  // Anything that isnt FF and isnt a single button returns -2 to indicate that multiple buttons are pressed
  String currentBank = "Two Pressed";
  int footID = -2;
  switch(hex)
  {
    case(0xfe):
      currentBank = FOOT_BANKS[0];
      footID = 0;
      break;
    case(0xfd):
      currentBank = FOOT_BANKS[1];
      footID = 1;
      break;
    case(0xfb):
      currentBank = FOOT_BANKS[2];
      footID = 2;
      break;
    case(0xf7):
      currentBank = FOOT_BANKS[3];
      footID = 3;
      break;
    case(0xef):
      currentBank = FOOT_BANKS[4];
      footID = 4;
      break;
    case(0Xff):
      currentBank = "none"; 
      footID = -1;
      break;
  }
  //Serial.print(currentBank) + "  ";
  return footID;
}


void changeFootLED(int ledID, bool isOn){
  if(isOn){
    digitalWrite(ledExpander,ledID, HIGH);
  } else {
    digitalWrite(ledExpander,ledID, LOW);
  }
}

void turnOffAllFootLEDs(){
  for(int i = 0; i<5; i++){
    changeFootLED(i,false);
  }
}

void sendRelay(PCF8574 address, int internalPin, int value){
  digitalWrite(address, internalPin, value);
}

void sendPhaseRelay(int loopID){
  byte leftIsReversed = LOW;
  byte rightIsReversed  = LOW;
  switch(current.phase[loopID]){

    case(0):
      leftIsReversed = LOW;
      rightIsReversed = LOW;
    break;

    case(1):
      leftIsReversed = LOW;
      rightIsReversed = HIGH;
    break;

    case(2):
      leftIsReversed = HIGH;
      rightIsReversed = LOW;
    break;

    case(3):
      leftIsReversed = HIGH;
      rightIsReversed = HIGH;
    break;
  }
    sendRelay(LeftPhaseRelays, loopID ,leftIsReversed);
    sendRelay(RightPhaseRelays, loopID ,rightIsReversed);
    Serial.println("Left Phase sent: " +String(leftIsReversed) + "Right Phase Sent: " +  String(rightIsReversed));
}

void initializeRelays(){
  //Return Relays
  for(int i = 0; i< 8; i++){
    sendReturnRelay(i,current.returns[i]); //CurrentReturns[i]
  //Phase Relays
    sendPhaseRelay(i);
  }
}

void highLightReturn(int id, bool shouldHighlight){
  String color = shouldHighlight ? HIGHLIGHT_COLOR : DEFAULT_COLOR;
  Serial2.print(ADDRESS_FOR_DISPLAY[id][2] + ".pco=" + color);
  sendEndCommand();
}

void sendReturnRelay(int id, bool onOrOff){
  Serial.println("Relay Value: " + String(onOrOff));
  sendRelay(ReturnRelayExpander,id,onOrOff);
}

void sendDelayTrails(){
  for(int i = 0; i < 7; i++){
    if(current.delayTrails[i]){ //CurrentDelayTrails[i]
      MatrixLeft.writeData(true,i,7);
      MatrixRight.writeData(true,i,7);
    }
  }
}

void checkDelayTrails(int durationInSeconds){
  
}

void DelayTrailStartCounter(){
  DelayTrailsPreviousMillis = millis();
}

void copyPreset(PresetData &current, PresetData &newPreset){
  current.presetID = newPreset.presetID;
  current.bankID = newPreset.bankID;
  memmove(current.loopPositions,newPreset.loopPositions, sizeof(newPreset.loopPositions));
  memmove(current.inputVolumes,newPreset.inputVolumes,sizeof(current.inputVolumes));
  memmove(current.leftOutputVolumes,newPreset.leftOutputVolumes,sizeof(current.leftOutputVolumes));
  memmove(current.rightOutputVolumes,newPreset.rightOutputVolumes,sizeof(current.rightOutputVolumes));
  memmove(current.phase,newPreset.phase,sizeof(current.phase));
  memmove(current.returns,newPreset.returns,sizeof(current.returns));
  memmove(current.delayTrails,newPreset.delayTrails,sizeof(current.delayTrails));
  memmove(current.delayTrailsTimeSeconds,newPreset.delayTrailsTimeSeconds,sizeof(current.delayTrailsTimeSeconds));
}



void changePreset(int id){
Serial.println(String(current.presetID));
copyPreset(presets[current.presetID],current);
copyPreset(current, presets[id]);

//send all data to hardware
MatrixLeft.writeArray(current.loopPositions,7);
MatrixLeft.writeArray(current.loopPositions,7);

for (size_t i = 0; i < 8; i++)
{
  sendPhaseRelay(i);

  digitalPotWrite(potID[LEFT_INPUT_VOLUME_POTS_IDS[1][i]],LEFT_INPUT_VOLUME_POTS_IDS[0][i],current.inputVolumes[i]); //CurrentInputVolumes[id]
  digitalPotWrite(potID[RIGHT_INPUT_VOLUME_POTS_IDS[1][i]],RIGHT_INPUT_VOLUME_POTS_IDS[0][i],current.inputVolumes[i]);
  digitalPotWrite(potID[LEFT_OUTPUT_VOLUME_POTS_IDS[1][i]],LEFT_OUTPUT_VOLUME_POTS_IDS[0][i],current.leftOutputVolumes[i]); //CurrentLeftOutputVolumes[id]
  digitalPotWrite(potID[RIGHT_OUTPUT_VOLUME_POTS_IDS[1][i]],RIGHT_OUTPUT_VOLUME_POTS_IDS[0][i],current.rightOutputVolumes[i]); //CurrentRightOutputVolumes[id]

  sendReturnRelay(i, current.returns[i]); // not sure
}

// send all data to Nextion
sendLoopPositionsNextion();
for (size_t i = 0; i < 8; i++)
{
  sendPhaseToNextion(i);
  sendVolumeToNextion(i,current.inputVolumes[i]);
  sendVolumeToNextion(i,current.leftOutputVolumes[i]);
  sendVolumeToNextion(i,current.rightOutputVolumes[i]);
  sendReturnNextion(i);
}

} 
