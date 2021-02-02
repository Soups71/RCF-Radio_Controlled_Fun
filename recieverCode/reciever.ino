//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
//create an RF24 object
RF24 radio(9, 10);  // CE, CSN
int arr[2];

// Initialization of Servos
Servo left;
Servo right;
int initial_arr[2];
//address through which two modules communicate.
const byte address[6] = "00001";
int i = 0;
void setup()
{
  while (!Serial);
    Serial.begin(9600);
  radio.begin();  
  //set the address
  radio.openReadingPipe(0, address);
  //Set module as receiver
  radio.startListening();

  // Left forward value is 0
  left.attach(5);
  // Right forward value is 180
  right.attach(6);

}

void loop()
{
  if (radio.available())
  {
    radio.read(&initial_arr, sizeof(initial_arr));
    initial_arr[0] = initial_arr[0]-512;
    initial_arr[1] = initial_arr[1]-512;
    arr[0] = initial_arr[0]-initial_arr[1];
    arr[1] = initial_arr[0]+initial_arr[1];
    int rightVal = map(arr[0], -512, 512, 0, 180);
    int leftVal = map(arr[1], -512, 512, -180, 0);
//    int rightVal = rightForVal + rightBackVal; 
//    int leftVal = leftForVal + leftBackVal;
    Serial.print(rightVal);
    Serial.print(",  ");
    Serial.println(leftVal);
    left.write(leftVal*-1);
    right.write(rightVal);
  }
}
