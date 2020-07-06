#include <Arduino.h>
#line 1 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino"

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

uint32_t Ttime, dTtime;            // integer for storing total time of a cycle
float frequency;        //storing frequency
float obroty;
const int buttonPin = 2;     // the number of the pushbutton pin
uint32_t screenupdateTime = micros();;
#line 19 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino"
void setup();
#line 34 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino"
void loop();
#line 19 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino"
void setup() {
  Wire.begin();
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
  oled.setFont(Adafruit5x7);
  oled.set1X();
}

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
uint32_t startPulse, stopPulse;

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
        stopPulse = micros();
        Ttime = stopPulse - startPulse;
        startPulse = micros();
  
        frequency=1000000.0/Ttime;    //getting frequency with Ttime is in Micro seconds
        obroty = frequency * 60.0;

      } else {
      ;
    }
  }
  lastButtonState = buttonState;

    if (micros() > screenupdateTime + 1000000) {
      oled.clear();
      oled.println(Ttime);
      oled.println(frequency);
      oled.println(obroty);
      screenupdateTime = micros();
    }
}

