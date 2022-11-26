# include <common.h>

//-----------------------------MATRIX----------------------------
AGD2188 MatrixRight(RIGHT_MATRIX_ADDRESS); 
AGD2188 MatrixLeft(LEFT_MATRIX_ADDRESS);

//------------------------------MENU------------------------------
enum E_MenuState {LOOPS = 1,INPUT_VOLUMES = 2, LEFT_OUTPUT_VOLUMES = 3,RIGHT_OUTPUT_VOLUMES = 4, PHASE = 5, NUM_MENU_OPTIONS = 6};
E_MenuState MenuState;
unsigned long PreviousMillis = 0;
unsigned long CurrentTime = 0;
int PreviousRotaryButtonValue;
int PreviousFootValue;
int FirstFootButtonValue = 0;
int SecondFootButtonValue = 0;

//------------------------------DATA------------------------------ 
int CurrentLoopPositions[7] = {0,0,0,0,0,0,0};
int CurrentInputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int CurrentLeftOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int CurrentRightOutputVolumes[8] = {DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME,DEFAULT_VOLUME};
int CurrentPhase[8] = {0,0,0,0,0,0,0,0};
bool CurrentReturns[8] = {1,1,1,1,1,1,1,1};
int TestArray[] = {0,1,0,3,0,0,0};

//----------------------Function prototypes------------------------
void updateUI(bool isClockwise, int id);
void changeLoopPositions(bool isClockwise, int id);
void sendLoopPositions();
void cycleMenu();
void changeVolume(int id, bool isClockwise, int volume_array[]);
void changePhase(int id, bool isClockwise);
void highlightMenu(bool shouldHighlight);
void changeReturn(int id);
void startCounter();
bool checkPress(int durationInSeconds, int id);
void sendReturn(int arrayId);
void initializeDisplay();
void doButton();
void doFoot();
void setVolumesDefault();
void sendVolumeToDigitalPot(int id);
void changeFootLED(int ledID, bool isOn);
int footHextoID(byte hex);
//----------------------------Buttons/RotaryEncoders---------------------------
EasyRotary RotaryEncoders(ROTARY_ENCODER_INTERUPT_PIN); //for reading rotary encoder data **NOT BUTTONS**
RotaryData RotaryDataStuct; // struct for holding rotary encoder data
PCF8574 rotaryExpander(ROTARY_BUTTONS_ADDRESS); // rotary encoder **BUTTONS**
PCF8574 footExpander(FOOTSWITCH_ADDRESS); // foot switch buttons
PCF8574 ledExpander(FOOT_SWITCH_LIGHTS_ADDRESS);
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
  i2CScan();

  initializeDisplay();
 
	pinMode(rotaryExpander, 0, INPUT_PULLUP);
  pinMode(footExpander, 1, INPUT_PULLUP);
  
  pinMode(ROTARY_INTERUPT_PIN, INPUT_PULLUP);
  pinMode(FOOT_INTERUPT_PIN,INPUT_PULLUP);

  RotaryEncoders.startup(*updateUI); //  if interupt occured calls UpdateUI()

  attachInterrupt(digitalPinToInterrupt(ROTARY_INTERUPT_PIN), ROTARY_INTERUPT, FALLING);
  attachInterrupt(digitalPinToInterrupt(FOOT_INTERUPT_PIN),FOOT_INTERUPT,FALLING);

  SPI.begin();
  
  pinMode(cs0_pin, OUTPUT);
  pinMode(cs1_pin, OUTPUT);
  pinMode(cs2_pin, OUTPUT);
  pinMode(cs3_pin, OUTPUT);
  pinMode(cs4_pin, OUTPUT);
  pinMode(cs5_pin, OUTPUT);
  setVolumesDefault();

  MatrixRight.wipeChip();
  MatrixLeft.wipeChip();

  MatrixRight.writeArray(CurrentLoopPositions,7);
  MatrixLeft.writeArray(CurrentLoopPositions,7);
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
}
//-----------------------------------------------------------------------------

void updateUI(bool isClockwise, int id){
  
  switch (MenuState){
    case (E_MenuState::LOOPS):
      if(id!=8){
        changeLoopPositions(isClockwise, id);
        sendLoopPositions();
        MatrixRight.writeArray(CurrentLoopPositions,7);
        MatrixLeft.writeArray(CurrentLoopPositions,7);
        }
      break;

    case(E_MenuState::INPUT_VOLUMES):
      changeVolume(id, isClockwise, CurrentInputVolumes);
      break;

    case(E_MenuState::LEFT_OUTPUT_VOLUMES):
      changeVolume(id, isClockwise, CurrentLeftOutputVolumes);
      break;
    
    case(E_MenuState::RIGHT_OUTPUT_VOLUMES):
      changeVolume(id, isClockwise, CurrentRightOutputVolumes);
      break;
    
    case(E_MenuState::PHASE):
      if(id!=8){
        changePhase(id, isClockwise);
      }
      break;
    }
  }
 
 void changeLoopPositions(bool isClockwise, int id){
   int loopArrayPosition = id-1;
   int loopArrayValue = CurrentLoopPositions[loopArrayPosition];
   if(loopArrayPosition!=7){
   if(isClockwise){
      loopArrayValue==7 ? CurrentLoopPositions[loopArrayPosition] = 0 : CurrentLoopPositions[loopArrayPosition]++;
   } else {
      loopArrayValue==0 ? CurrentLoopPositions[loopArrayPosition] = 7 : CurrentLoopPositions[loopArrayPosition]--;
   }
   }
 }

  void sendLoopPositions(){
    for(int i = 0; i < 8; i++){
    Serial2.print(LOOPS_FOR_DISPLAY[i] + ".val=" + String(CurrentLoopPositions[i]));
    sendEndCommand();
  }
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
    isClockwise ? volume[idToArray]++ : volume[idToArray]--;
    capVolume(volume, idToArray);
    int volumeForDisplay = volumeToDisplay(volume[idToArray]);
    sendVolumeToDisplay(idToArray, volumeForDisplay); 
    sendVolumeToDigitalPot(idToArray);
}

void sendPhase(int arrayId){
  String left_phase = "";
  String right_phase = "";
  int PHASE = CurrentPhase[arrayId];

  if(PHASE == 0){
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
    if(CurrentPhase[idToArray] == 3){
      CurrentPhase[idToArray] = 0;
    } else {
      CurrentPhase[idToArray]++;
    }
  } else {
    if(CurrentPhase[idToArray]==0){
      CurrentPhase[idToArray] = 3;
    } else {
      CurrentPhase[idToArray]--;
    }
  }
 sendPhase(idToArray);
}

void sendReturn(int arrayId){
    String returnToDisplay = CurrentReturns[arrayId] ? STEREO : MONO;
    Serial2.print(ADDRESS_FOR_DISPLAY[arrayId][2] + ".txt=" + '"' + returnToDisplay + '"');
    sendEndCommand();
    Serial.println(ADDRESS_FOR_DISPLAY[arrayId][2] + ".txt=" + '"' + returnToDisplay + '"');
}

void changeReturn(int id){
  int idToArray = id -1;
  if(idToArray!=7){
    CurrentReturns[idToArray] = !CurrentReturns[idToArray];
    sendReturn(idToArray);
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

  
void initializeDisplay(){
  //Phases
  for(int i = 0; i <7; i++){
      sendPhase(i);
  }
  //Loops
    sendLoopPositions();
    sendEndCommand();
    MenuState = E_MenuState::INPUT_VOLUMES;
  //Input Volumes
  for(int i = 0; i <8; i++){
    sendVolumeToDisplay(i, volumeToDisplay(CurrentInputVolumes[i])); 
  }
  //Return
  for(int i = 0; i<7; i++){
    sendReturn(i);
  }
  //Left Output
  MenuState = E_MenuState::LEFT_OUTPUT_VOLUMES;
  for(int i = 0; i <8; i++){
    sendVolumeToDisplay(i, volumeToDisplay(CurrentLeftOutputVolumes[i])); 
  }
  //Right Output
  MenuState = E_MenuState::RIGHT_OUTPUT_VOLUMES;
  for(int i = 0; i <8; i++){
    sendVolumeToDisplay(i, volumeToDisplay(CurrentRightOutputVolumes[i])); 
  }
  //Unhighlight
  for(int i = 1; i <6; i++){
    MenuState = static_cast<E_MenuState>(i);
    highlightMenu(false);
  }

  for(int i = 0; i < 5; i++){

  }

  //Highlight Loops First and set MenuState
  MenuState = E_MenuState::LOOPS;
  highlightMenu(true); 
}

void doButton(){
    RotaryFlag = false;
        int RotaryButtonValue = rotaryExpander.read();
        if(RotaryButtonValue!=0xFF && RotaryButtonValue!=PreviousRotaryButtonValue){
          startCounter();
        }
        Serial.print("READ Knobs:\t");
        Serial.println(RotaryButtonValue, HEX);
        if(RotaryButtonValue == 0xFF && RotaryButtonValue!=PreviousRotaryButtonValue){
          int id = rotaryHexToId(PreviousRotaryButtonValue);
          checkPress(LONG_PRESS_INTERVAL_S,id) ? changeReturn(id) : cycleMenu();
        }
          PreviousRotaryButtonValue = RotaryButtonValue;
}

void doFoot(){   
        FootFlag = false;
        int footID = footHextoID(footExpander.read());

        // when 2 are pressed and when released sends original hex again aka the other one pressed

        if(footID != PreviousFootValue){
  
          // if(footID != -1 && FirstFootButtonValue == -2){
          //   FirstFootButtonValue = footID;
          // }

          // if(footID != -1 && footID != FirstFootButtonValue && FirstFootButtonValue != -2){
          //   SecondFootButtonValue = footID;
          // }

          // if(footID == -1){
          //   Serial.println("First Button: " + String(FirstFootButtonValue) + " Second Button: " + String(SecondFootButtonValue)); 
          //   FirstFootButtonValue = -2;
          //   SecondFootButtonValue = -2;
          // }
        }
        PreviousFootValue = footID;
}


void setVolumesDefault(){
for(int i = 0; i<36; i++){
  digitalPotWrite(i, DEFAULT_VOLUME);
}

}

void sendVolumeToDigitalPot(int id){

  switch (MenuState)
  {
    case(E_MenuState::INPUT_VOLUMES):
      digitalPotWrite(INPUT_VOLUMES_POTS_IDS[0][id], CurrentInputVolumes[id]);
      digitalPotWrite(INPUT_VOLUMES_POTS_IDS[1][id], CurrentInputVolumes[id]);
      break;
  
    case(E_MenuState::LEFT_OUTPUT_VOLUMES):
      digitalPotWrite(LEFT_OUTPUT_VOLUMES_POTS_IDS[id], CurrentLeftOutputVolumes[id]);
      break;

    case(E_MenuState::RIGHT_OUTPUT_VOLUMES):
      digitalPotWrite(RIGHT_OUTPUT_VOLUMES_POTS_IDS[id], CurrentRightOutputVolumes[id]);
      break;
  }
}


int footHextoID(byte hex){
  String currentBank = "none";
  int footID = -1;
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
  }
  //Serial.println("FootID:" + String(footID));
  return footID;
}


void changeFootLED(int ledID, bool isOn){
  if(isOn){
    digitalWrite(ledExpander,ledID, HIGH);
  } else {
    digitalWrite(ledExpander,ledID, LOW);
  }
}

