#include <Arduino.h>
#include "TCA9548A.h"
#include <Wire.h>
TCA9548A I2CMux;                  // Address can be passed into the constructor
float temp0;
float temp1;
#include <Adafruit_NeoPixel.h>
#include "colors.h"
const int PIXELPIN = 8;
const int PIXELCOUNT = 12;
Adafruit_NeoPixel pixel( PIXELCOUNT , PIXELPIN , NEO_GRB + NEO_KHZ800 );

#include <Adafruit_TCS34725.h>
byte gammatable[256];   //  RGB -> eye-recognized gamma color

Adafruit_TCS34725 tcs0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);


  //  Wire.setPins(21, 22);// ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire to the library (the line below).

  I2CMux.begin(Wire);             // Wire instance is passed to the library

  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop()
{

  I2CMux.openChannel(0);

  I2CMux.closeChannel(0);

  I2CMux.openChannel(2);
  float red;
  float green;
  float blue;
  int color;
  tcs0.begin();
  tcs0.setInterrupt(false);  // turn on LED
  tcs0.getRGB(&red, &green, &blue);
  delay(60);

  //tcs.setInterrupt(true);  // turn off LED
  int r = red;
  int g = green;
  int b = blue;

  Serial.printf( "%i", g);
  if ( r > 1.5 * b && r > 1.5 * g) {
    color = 0xFF0000;
  }
  //if (g >  b && g > r) {
    //color = 0x008000;
  //}
  if (b > 1.5 * g && b > 1.5 * r) {
    color = 0x0000FF;;
  }
    pixel.fill(color, 0, 12);
    pixel.setBrightness(40);
    pixel.show();
  I2CMux.closeChannel(2);
  


  
  //I2CMux.closeAll();
}


  void tcs0Read() {

  // declare color variables
  uint16_t Clear;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  float r;
  float g;
  float b;
  //turn on LED
  tcs0.setInterrupt(false);
  // delay(60)= take 60ms to read sensor data.Setup timer for this
  // read the sensor
  tcs0.getRawData(&red, &green, &blue, &Clear);
  // turn off LED
  tcs0.setInterrupt(true);
  unsigned int sum = Clear;
  r = red;
  r /= sum;
  g = green;
  g /= sum;
  b = blue;
  b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;
  Serial.printf("%i,%i,%i \n" , r, g,b);
}
