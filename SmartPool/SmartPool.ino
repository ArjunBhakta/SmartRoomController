#include <ClosedCube_TCA9548A.h>

#include <Wire.h>

/*
  Project : SPOOL- Smart Pool Table
  Description: Smart Room Device
  Author: Arjun Bhakta
  Date: 17-FEB-2022
*/

// servo Initialize
#include <PWMServo.h>
PWMServo myServo0;
PWMServo myServo1;
PWMServo myServo2;
PWMServo myServo3;

// RGB Sensor Initialize // Source: https://pastebin.com/ePirav1a

#include <Adafruit_TCS34725.h>
byte gammatable[256];   //  RGB -> eye-recognized gamma color

Adafruit_TCS34725 tcs0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// NeoPixel + colors.h Initialize
#include <Adafruit_NeoPixel.h>
#include "colors.h"
const int PIXELPIN = 2;
const int PIXELCOUNT = 12;
Adafruit_NeoPixel pixel ( PIXELCOUNT , PIXELPIN , NEO_GRB + NEO_KHZ800 );

// bool for photoResitor Values
bool p0;
bool p1;
bool p2;
bool p3;

//

bool y;
bool hasRun = true;
int bri;

void setup() {
  Serial.begin(9600);
  tcs0.begin();
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i = 0; i < 256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;




  pinMode(14, INPUT);
  pinMode(15, INPUT); // PhotoResistor
  myServo0.attach(22);
  myServo1.attach(23);// Servo Motor
  pinMode(12, OUTPUT); // NEOpixels
  pixel.begin();
  pixel.show();

  bri = 40;

}
}

//void shootAroundMode();
//void twoBallMode();



void loop() {

  // define photoresistor state at each pocket
  p0 = photoRead(15);
  p1 = photoRead(14);
  // p2 = photoRead();
  // p3= photoRead();



  // set pixel color based on reading at each pocket
  if (p0 == 1) {
    pixel.fill(0x000000, 0, 4 );
    pixel.setBrightness(bri);
    pixel.show();
    myServo0.write(p0 * 180);
  }
  else {
    myServo0.write(p0 * 180);
    pixel.fill(blue, 0, 4 );
    pixel.setBrightness(bri);
    pixel.show();
  }


  if (p1 == 1) {

    pixel.fill(0, 4, 4 );
    pixel.setBrightness(bri);
    pixel.show();
    myServo1.write(p1 * 180);
  }
  else {
    myServo1.write(p1 * 180);
    pixel.fill(0xe1ad01, 4, 4);
    pixel.setBrightness(bri);
    pixel.show();
  }
}

bool photoRead(int _prPin) {
  int pRead;
  bool pVal;
  bool photoState;
  bool prePhotoState;
  pRead = analogRead(_prPin);
  if (pRead < 200) {
    pVal = 0;
  }
  else {
    pVal = 1;
  }
  if (pVal != prePhotoState) {
    if (pVal == false) {
      photoState = !photoState;
    }
    photoState = prePhotoState;
  }

  Serial.printf("%i\n", photoState);
  return photoState;
}

// output will result in color
void tcsRead(bool _readColor) {
  
  // declare color variables
  unsigned int Clear;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
  
  float r, g, b;


  //turn on LED
  tcs0.setInterrupt(false);

  // delay(60)= take 60ms to read sensor data.Setup timer for this

  // read the sensor
  tcs0.getRawData(&red, &green, &blue, &Clear);
  // turn off LED
  tcs0.setInterrupt(true);
  unsigned int sum = Clear;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  

}
// output will release ball
void servoAction() {

}

//

void WemoAction(bool _buttonState) {

}
