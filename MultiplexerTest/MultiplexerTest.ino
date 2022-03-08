#include <Arduino.h>
#include "TCA9548A.h"
#include <Wire.h>
TCA9548A I2CMux;                  // Address can be passed into the constructor
#include <Adafruit_BME280.h>
Adafruit_BME280 bme0;
Adafruit_BME280 bme1;
float temp0;
float temp1;


void setup() {
  Serial.begin(9600);

  //  Wire.setPins(21, 22);// ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire to the library (the line below).

  I2CMux.begin(Wire);             // Wire instance is passed to the library

  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop()
{

  I2CMux.openChannel(0);
  bme0.begin(0x76);
  temp0 = bme0.readTemperature();
  I2CMux.closeChannel(0);

  I2CMux.openChannel(2);
  bme1.begin(0x76);
  temp1 = bme1.readTemperature();
  I2CMux.closeChannel(2);
  

  Serial.printf("%.2f,%.2f \n" , temp0, temp1);


  
  //I2CMux.closeAll();
}
