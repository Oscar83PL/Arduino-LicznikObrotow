# 1 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino"

# 3 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino" 2
# 4 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino" 2
# 5 "c:\\Users\\Oskar\\Desktop\\Projekty\\20. Arduino\\Arduino-LicznikObrotow\\Arduino-LicznikObrotow.ino" 2

// 0X3C+SA0 - 0x3C or 0x3D


// Define proper RST_PIN if required.


SSD1306AsciiWire oled;

uint32_t Ttime, dTtime; // integer for storing total time of a cycle
float frequency; //storing frequency
float obroty;
const int buttonPin = 2; // the number of the pushbutton pin
uint32_t screenupdateTime = micros();;
void setup() {
  Wire.begin();

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, 0x0);

  oled.begin(&Adafruit128x32, 0x3C, -1);
  oled.setFont(Adafruit5x7);
  oled.set1X();
}

int buttonState = 0; // current state of the button
int lastButtonState = 0; // previous state of the button
uint32_t startPulse, stopPulse;

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == 0x1) {
        stopPulse = micros();
        Ttime = stopPulse - startPulse;
        startPulse = micros();

        frequency=1000000.0/Ttime; //getting frequency with Ttime is in Micro seconds
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
