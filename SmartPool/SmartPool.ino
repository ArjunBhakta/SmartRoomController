
/*
  Project : SPOOL- Smart Pool Table
  Description: Smart Room Device
  Author: Arjun Bhakta
  Date: 7-MAR-2022
*/

#include "IotTimer.h"

IoTTimer servoTimer;
const int TIME_SERVO = 1000;
bool isOpen1;
bool hasRun = false;
bool hasRun1 = false;
IoTTimer ballTimer;
const int BALL_SERVO = 2000;

// counter
bool lastBallState;
bool currentBallState;
int ballCount;

//Wemo/HueLights
#include <SPI.h>
#include <Ethernet.h>
#include <mac.h>
#include <Encoder.h>
#include <wemo.h>
#include <hue.h>

//// Multiplexer i2c
//#include <TCA9548A.h>
//#include <Wire.h>
//TCA9548A I2CMux;
////I2CMux.begin(Wire);             // Wire instance is passed to the library
////I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)

// servo Initialize
#include <PWMServo.h>
PWMServo myServo0;
PWMServo myServo1;
PWMServo myServo2;
PWMServo myServo3;

int gateColor = 0;

#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// NeoPixel + colors.h Initialize
#include <Adafruit_NeoPixel.h>
#include "colors.h"
const int PIXELPIN = 1;
const int PIXELCOUNT = 30;
Adafruit_NeoPixel pixel (PIXELCOUNT , PIXELPIN , NEO_GRB + NEO_KHZ800 );

// bool for photoResitor Values
bool p1;
//
int bri;

//OLED
#include <Adafruit_SSD1306.h>
#include <splash.h>
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1; // makes this the same as Teensy Reset Button
const int SCREEN_ADDRESS = 0x3C ; // recieved this from I2C scanner
int rot = 0;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //&WIre = Wire.begin()

int h;

void setup() {
  Serial.begin(9600);
  pinMode(22, INPUT_PULLUP);
  tcs.begin();
  ballCount = 0;

  pinMode(14, INPUT);
  pinMode(15, INPUT); // PhotoResistor
  myServo1.attach(23);// Servo Motor
  pinMode(1, OUTPUT); // NEOpixels
  pixel.begin();
  pixel.show();

  
  Ethernet.begin(mac);
  //printIP();
  //wemoButton
  myServo1.write(180);

  // oled

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setRotation(90);
  int gateColor;

}

void loop() {

  //Serial.printf ("%i \n" , ballCount);

  // define photoresistor state at each pocket
  //p0 = photoRead(15);
  p1 = photoRead(14);
  //Serial.printf ("%i \n" , p1);

  if (p1 == 1) {
    lastBallState = 1;
    neoPixelsDisplay(gateColor,0,30);
    //hasRun1 = false;
  }
  else {

    gateColor = tcsColor();
    neoPixelsDisplay(gateColor, 0, 30);

    if ((hasRun == false)) {
      servoTimer.startTimer(TIME_SERVO);
      myServo1.write(0);
      hasRun = true;
      gateColor = tcsColor();
      //Serial.printf ("timer started");
    }
  }
  //Serial.printf ("%i,%i\n",servoTimer.isTimerReady(),hasRun);
  if (servoTimer.isTimerReady() && hasRun) {
   // Serial.printf ("closeServo\n");
    myServo1.write(180);
    hasRun = false;
    currentBallState = 0;
    if (lastBallState != currentBallState) {
      ballCount++;
      lastBallState = currentBallState;
      //hasRun = true;

    }
  }
  oledDisplay();
  HueLights(ballCount);

  //Serial.printf("%i\n", ballCount);
  if (ballCount == 8) {
    for (h=1;h<5; h++){
    setHue(h, false, 0, 0, 0);
    Serial.printf ("hueoff");
    }
    ballCount = 1;
  }

  distractMode(22);
 
}


//
bool photoRead(int _prPin) {
  int pRead;
  bool pVal;
  bool photoState;
  bool prePhotoState = false;
  pRead = analogRead(_prPin);

  if (pRead < 50) {
    pVal = 0;
  }
  else {
    pVal = 1;
  }
  //Serial.printf("%i, %i\n", pRead, pVal);
  return pVal;
}

void distractMode(int buttonPin) {
  static bool lastButtonState;
  bool curButtonState = digitalRead(buttonPin);
  int i;
  int j;
  if ( lastButtonState && curButtonState == 0) {
    for ( i = 0; i < 5; i++) {
      switchON(i);
    }
    lastButtonState= !lastButtonState;
  }
   if (lastButtonState ==false && curButtonState == 1) {
    for (j = 0; j < 5; j++) {
      switchOFF(j);
    }
    lastButtonState=true; 
}
}

void HueLights(int _ballCount) {
  int rState;
  int hueIndex;
  int bright;
  IoTTimer HueTimer;
  const int HUE_TIME = 2000;
  bool hueRun;
  bool cycleRun;
  cycleRun = false;
  hueRun == false;
  int h;
if (gateColor == red){
  hueIndex = 0;
}
if (gateColor == yellow){
  hueIndex = 2;
}
if (gateColor == green){
  hueIndex = 3;
}
if (gateColor ==blue){
  hueIndex = 4;
}
if (gateColor ==purple){
  hueIndex = 6;
}
    if (ballCount == 6) {
    for (h=1;h<5; h++){
    setHue(h, true, HueRainbow[hueIndex], 200, 255);
    Serial.printf ("hue");
    hueRun = true; 
    }
    
  }

  
//  if (HueTimer.isTimerReady() && hueRun == true) {
//    rState++;    
//  }
  //  if (HueTimer.isTimerReady() && hueRun == false && _ballCount ==7) {
  //    setHue(1, false, 0, 0, 0);
  //    hueRun = false;
  //    _ballCount = 0;
  //  }

}

void neoPixelsDisplay(int _colorValue, int _pixelStart, int _pixelNum) {
  int bright;
  bright = 40;
  pixel.fill(_colorValue, _pixelStart, _pixelNum);
  pixel.setBrightness(bright);
  pixel.show();
}

void neoPixelClear(int _pixelStart, int _pixelNum) {
  pixel.fill(0x000000, _pixelStart, _pixelNum);
  pixel.show();
}

void oledDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  display.printf("%i %i", ballCount, gateColor);
  display.display();
}
int tcsColor() {
  float hue;
  float r1;
  float g1;
  float b1;
  int hue1;
  int hueMapped;
  int closeHue;
  int minHue;
  int hueArray[] = {0, 30, 70, 210, 350, 360};
  int i;
  int h;
  float red1;
  float green1;
  float blue1;
  int color;

  tcs.setInterrupt(false);  // turn on LED
  tcs.getRGB(&red1, &green1, &blue1);
  delay(5);
  tcs.setInterrupt(true);  // turn off LED
  delay(5);
  int  r = red1;
  int g = green1;
  int b = blue1;
  r1 = r / 255.0;
  g1 = g / 255.0;
  b1 = b / 255.0;

  //If Red is max, then Hue = (G-B)/(max-min)
  //If Green is max, then Hue = 2.0 + (B-R)/(max-min)
  //If Blue is max, then Hue = 4.0 + (R-G)/(max-min)

  if ( r1 > g1 && r1 > b1 ) {
    hue =  (g1 - b1) / (r1 - min(g1, b1));
  }
  if ( g1 > r1 && g1 > b1 ) {
    hue =  2.0 + (b1 - r1) / (g1 - min(r1, b1));
  }
  if ( b1 > r1 && b1 > g1 ) {
    hue =  4.0 + (r1 - g1) / (b1 - min(g1, r1));
  }
  hue1 = hue * 60;
  if (hue1 < 0) {
    hue1 = hue1 + 360;
  }

  minHue = 360;
  for (i = 0; i < 6; i++) {
    h = hue1 - hueArray[i];
    if (abs(h) < minHue) {
      minHue = abs(h);
      closeHue = i;
    }
  }
  if (closeHue == 0 || closeHue == 5) {
    color = red;
  }
  if (closeHue == 1) {
    color = yellow;
  }
  if (closeHue == 2) {
    color = green;
  }
  if (closeHue == 3) {
    color = blue;
  }
  if (closeHue == 5) {
    color = purple;
  }
  return color;
}
void printIP() {
  Serial.printf("My IP address: ");
  for (byte thisByte = 0; thisByte < 3; thisByte++) {
    Serial.printf("%i.", Ethernet.localIP()[thisByte]);
  }
  Serial.printf("%i\n", Ethernet.localIP()[3]);
}
