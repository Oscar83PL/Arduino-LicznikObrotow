#include "TM1637.h"

#define CLK_A 4
#define DIO_A 3
#define CLK_B 6
#define DIO_B 5

TM1637 out_Display_A(CLK_A,DIO_A);
TM1637 out_Display_B(CLK_B,DIO_B);

int8_t Disp_A[] = {0x00,0x00,0x00,0x00};
int8_t Disp_B[] = {0x00,0x00,0x00,0x00};

uint32_t Ttime_A, dTtime_A;
uint32_t Ttime_B, dTtime_B;

float frequency_A = 0, rev_per_minute_A = 0;
float frequency_B = 0, rev_per_minute_B = 0;

const int inPin_Pulse_A = 2; 
const int inPin_Pulse_B = 7;
 
uint32_t screenupdateTime = micros();

void setup()
{
    Serial.begin(9600);
    Serial.println("Start -----------------");

  
  
  pinMode(inPin_Pulse_A, INPUT);
  pinMode(inPin_Pulse_B, INPUT);

  out_Display_A.init();
  out_Display_A.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  out_Display_B.init();
  out_Display_B.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;


}

int inPinState_A = 0, lastinPinState_A = 0;
int inPinState_B = 0, lastinPinState_B = 0;

uint32_t startPulse_A = 0, stopPulse_A = 0;
uint32_t startPulse_B = 0, stopPulse_B = 0;

uint32_t rev_per_minute_Aa, rev_per_minute_Bb;

void loop()
{
  inPinState_A = digitalRead(inPin_Pulse_A);
  inPinState_B = digitalRead(inPin_Pulse_B);
  
  if (inPinState_A != lastinPinState_A)
  {
    if (inPinState_A == HIGH)
    {
      stopPulse_A   = micros();
      Ttime_A       = stopPulse_A - startPulse_A;
      startPulse_A  = micros();

      frequency_A       = 1000000.0 / Ttime_A; 
      rev_per_minute_A  = frequency_A * 60.0;
    }
    else
    {
      ;
    }
  }
  lastinPinState_A = inPinState_A;

  if (inPinState_B != lastinPinState_B)
  {
    if (inPinState_B == HIGH)
    {
      stopPulse_B   = micros();
      Ttime_B       = stopPulse_B - startPulse_B;
      startPulse_B  = micros();

      frequency_B       = 1000000.0 / Ttime_B; 
      rev_per_minute_B  = frequency_B * 60.0;
    }
    else
    {
      ;
    }
  }
  lastinPinState_B = inPinState_B;



  if (micros() > screenupdateTime + 1000000)
  {

    if (micros() > startPulse_A + 12000000)
    {
      rev_per_minute_A = 0;
    }
    if (micros() > startPulse_B + 12000000)
    {
      rev_per_minute_B = 0;
    }
    
    rev_per_minute_Aa = rev_per_minute_A;
    Disp_A[3] = rev_per_minute_Aa % 10;
    Disp_A[2] = (rev_per_minute_Aa / 10) % 10;
    Disp_A[1] = (rev_per_minute_Aa / 100) % 10;
    Disp_A[0] = (rev_per_minute_Aa / 1000) % 10;

    rev_per_minute_Bb = rev_per_minute_B;
    Disp_B[3] = rev_per_minute_Bb % 10;
    Disp_B[2] = (rev_per_minute_Bb / 10) % 10;
    Disp_B[1] = (rev_per_minute_Bb / 100) % 10;
    Disp_B[0] = (rev_per_minute_Bb / 1000) % 10;

    out_Display_A.display(Disp_A);
    out_Display_B.display(Disp_B);
    
    screenupdateTime = micros();
  }
}