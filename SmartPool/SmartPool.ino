/*
  Project : SPOOL- Smart Pool Table
  Description: Photo-Resistor/ RGB Sensor/ Servo Motor
  Author: Arjun Bhakta
  Date: 17-FEB-2022
*/
#include <PWMServo.h>
#include <Adafruit_NeoPixel.h>
#include "colors.h"
PWMServo myServo;
PWMServo myServo1;

const int PIXELPIN = 2;
const int PIXELCOUNT = 12;
Adafruit_NeoPixel pixel ( PIXELCOUNT , PIXELPIN , NEO_GRB + NEO_KHZ800 );

bool x0;
bool x1;
bool y;
bool hasRun = true;
int bri;

void setup() {
  pinMode(14, INPUT);
  pinMode(15, INPUT); // PhotoResistor
  myServo.attach(22);
  myServo1.attach(23);// Servo Motor
  pinMode(12, OUTPUT); // NEOpixels
  pixel.begin();
  pixel.show();

  bri = 40;

}

void loop() {
  x0 = photoRead(15);
  x1 = photoRead(14);
  //servoX(23,x);
  //servoX(22,y);
  if (x0 == 1) {
    pixel.fill(0x000000, 0,4 );
    pixel.setBrightness(bri);
    pixel.show();
    myServo.write(x0 * 180);
  }
  else {
    myServo.write(x0 * 180);
    pixel.fill(blue, 0,4 );
    pixel.setBrightness(bri);
    pixel.show();
  }

  
  if (x1 == 1) {
   
    pixel.fill(0, 4,4 );
    pixel.setBrightness(bri);
    pixel.show();
    myServo.write(x1 * 180);
  }
  else {
    myServo.write(x1 * 180);
    pixel.fill(0xe1ad01,4,4);
    pixel.setBrightness(bri);
    pixel.show();
  }
}

bool photoRead(int _prPin) {
  int pRead;
  bool pVal;
  pRead = analogRead(_prPin);
  if (pRead < 200) {
    pVal = 0;
  }
  else {
    pVal = 1;
  }

  Serial.printf("%i\n", pVal);

  return pVal;
}
