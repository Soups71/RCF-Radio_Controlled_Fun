//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
int vert = A0;   
int hori = A1;// select the input pin for the potentiomete
int verticalVal = 0;  // variable to store the value coming from the sensor
int horizontalVal = 0;
int arr[2];
void setup()
{
  Serial.begin(9600);
  radio.begin();
  //set the address
  radio.openWritingPipe(address);
  //Set module as transmitte
  radio.stopListening();
}
void loop()
{
  //Send message to receiver
 
  int forward = analogRead(vert);
  int left_right = analogRead(hori);
   arr[0] = forward;
   arr[1] = left_right; 
    for(int i =0; i<2; i++){
      Serial.print(arr[i]);
      Serial.print(", ");
  }
    Serial.println();
    
  radio.write(&arr, sizeof(arr));
  delay(50);
}
