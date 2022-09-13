#include <Arduino.h>
#include "MatrixLibrary.h"


AGD2188 matrix;
bool wipe_chip_once = true;
byte testByte = 0;
int test_array[8] {3,1,0,0,0,1,0,0}; // expected outcome should be to connect x7 to y1 and y5, then connect x1 and x5 to y0, then x0 to y7;

void ArrayToWrite(int input_array[8],int sizeOfArray); // This is a forward declaration 

void setup() {
  Serial.begin(115200);
  matrix = AGD2188();
}

void loop() {
   if(wipe_chip_once)
   {
   matrix.wipe_chip();
   wipe_chip_once = false;
   ArrayToWrite(test_array,8);
  // for (int i =0; i<8; i++){ TESTING
  //   for (int j =0; j<8; j++){
  //     matrix.write_data(true,i,j);
  //     matrix.read_data(i);
  //     delay(500);
  //   }
  // }


   }
  
}



void ArrayToWrite(int input_array[8], int sizeOfArray){
  // step One: find lowest number in array.
  int minVal = 7;
  for (int i = 0; i < sizeOfArray; i++){
    Serial.println(i);
    if(input_array[i] !=0 && input_array[i] < minVal){
      minVal = input_array[i];
    }
  }
  String output_message = "minVal: ";
  Serial.println(output_message + minVal);

  //Step Two: Assign input device to each of the positions with minVal;
  for (int i = 0; i < sizeOfArray; i++){
      if(input_array[i]==minVal){
         matrix.write_data(true,7,i);
       }
  }
  //matrix.read_data(7); uncomment to check

  //Step Three: iterate through and check for next value 
  int preVal = minVal;
  int curVal = minVal;

   for (int i = 0; i < sizeOfArray; i++){
    // 3.0 finds the next highest number in the array
    int interval = 1;
    for(int p = 0; p < sizeOfArray; p++){
      if(input_array[p]==(preVal+interval)){
        curVal = preVal+interval;
      }
      if(curVal == preVal && p == 7){
        interval ++;
        if(interval <6){
          p=-1;
        }
      }
    }
    // String m_message = "prev than cur: ";
    // m_message += preVal;
    // m_message += " , ";
    // m_message += curVal;
    // Serial.println(m_message);

    // 3.5 This connects all of the currently highest values to all of the previous highest values
    if(curVal!=preVal){
     for(int o = 0; o < sizeOfArray; o++){
      if(input_array[o]==curVal){
        for(int l = 0; l<sizeOfArray; l++){
          if(input_array[l]==preVal){
          matrix.write_data(true,o,l);
          }
        }
      }
    }
    preVal = curVal;
    }
   }
   // Step 4: Connect highest values to output
   for(int m = 0; m <sizeOfArray; m++){
    if(input_array[m]==curVal){
      matrix.write_data(true,m,7);
    }
   }
} 


