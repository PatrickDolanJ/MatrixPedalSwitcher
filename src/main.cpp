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
  // for (int i =0; i<8; i++){
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

  //Step Three: iterate through and checck for next value 
  int preVal = minVal;
  int curVal = minVal;

  // for (int i = 0; i < sizeOfArray; i++){
    // finds the next highest number in the array
    int interval = 1;
    for(int p = 0; p < sizeOfArray; p++){
      Serial.print(input_array[p]);
      if(input_array[p]==(preVal+interval)){
        curVal = preVal+interval;
      }
      if(curVal == preVal && p == 7){
        Serial.println(interval);
        interval ++;
        if(interval <6){
          p=-1;
        }
      }
    }
    String m_message = "prev than cur: ";
    m_message += preVal;
    m_message += " , ";
    m_message += curVal;
    Serial.print(m_message);

  //}
  




} 


