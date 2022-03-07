/*
  Project : SPOOL- Smart Pool Table
  Description: Photo-Resistor/ RGB Sensor/ Servo Motor
  Author: Arjun Bhakta
  Date: 17-FEB-2022
*/
#include <PWMServo.h>
PWMServo myServo;
bool y;

void setup() {
pinMode(14,INPUT); // PhotoResistor
pinMode(15,OUTPUT); // Servo Motor
pinMode(12,OUTPUT); // NEOpixels
 
}

void loop() {
y=photoRead(14);
servoX(15,y);
}

void photoRead(int _prPin){
  int pRead;
  bool pVal;
  pRead = analogRead(_prPin);
  if (pRead < 300) {
    pVal = 0;
  }
  else {
    pVal = 1;
  }
  Serial.printf("%i\n", pVal);

return pVal;
}

void servoX(int _servoPin,bool _x){
  
if(_x==1){
  myServo.write(180);
}
else{
  myServo.write(0);
}
}
