#include <Arduino.h>

int rotaryHexToId(byte hexVal){
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

  

