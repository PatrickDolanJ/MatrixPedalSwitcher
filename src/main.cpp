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

  //Step Three: iterate through and checck for next value 
  


} 