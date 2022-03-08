#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Wire.h>
/*
   Project: L010_01_OLEDWrite
   Description: scan the I
   Author: Arjun Bhakta
   Date: 28 Feb 2022
*/
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1; // makes this the same as Teensy Reset Button
const int SCREEN_ADDRESS = 0x3C ; // recieved this from I2C scanner
int rot = 0;
char color[7] = {'Y', 'B', 'R', 'P', 'G', 'O'};



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //&WIre = Wire.begin()

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setRotation(rot);
}

void loop() {

displayGameMode();
delay (1000);
display.clearDisplay();
displayShootAroundMode();
delay (1000);
}

void displayGameMode(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.cp437(true);
  display.printf("Player 1:%i \nPlayer 2:%i", 2, 3);
  display.display();
}

void displayShootAroundMode(){
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.cp437(true);
  display.printf("%s \n",color);
  display.display();
}
  
