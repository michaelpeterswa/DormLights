/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h" 

#define NUM_LEDS 150
#define DATA_PIN 5

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

//smoothing
//
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;
//
//

int color = 0;
int val = 175;
CRGB leds[NUM_LEDS];

void setup() 
{
   Serial.begin(9600);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
   //smoothing
   //
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
   //
   //
}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   //double volts = (peakToPeak * 5.0) / 1024;  // convert to volts

   //Serial.println(average);
   //color = 0;//random(0,255);
   int ptpConstCol = map(peakToPeak, 20, 300  , 160, 255);
   int currentCol = constrain(ptpConstCol, 160, 255);
   int ptpConst = map(peakToPeak, 20, 300  , 0, 73);
   int current = constrain(ptpConst, 0, 73);
   Serial.println(currentCol);
   for(int i = 0; i < current; i++){ 
    leds[75 + i] = CHSV(currentCol , 255, 255);
    leds[75 - i] = CHSV(currentCol , 255, 255);
    //leds[0 + (75 - i)] = CHSV(color , 255, 0); 
    //leds[149 - (75 - i)] = CHSV(color , 255, 0);
   }
   FastLED.show();
   for(int i = 0; i < NUM_LEDS; i++){ 
    leds[i] = CHSV(color , 255, 0);
   }
   }
