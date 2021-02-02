/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h" 
#include "arduinoFFT.h"

#define NUM_LEDS 150
#define DATA_PIN 5

//fft
//
#define SAMPLES 128           //Must be a power of 2
#define SAMPLING_FREQUENCY 5000 //Hz, must be less than 10000 due to ADC
//
//

//volume
//
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
//
//

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

int f = 0;
int val = 175;
CRGB leds[NUM_LEDS];

//fft
//
arduinoFFT FFT = arduinoFFT();
unsigned int sampling_period_us;
unsigned long microseconds;

struct HSV {
  int hue;
  int sat;
  int val;
};
 
double vReal[SAMPLES];
double vImag[SAMPLES];

HSV colorLED[150];
HSV black;
//
//
void setup() 
{
   Serial.begin(9600);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

   //fft
   //
   randomSeed(98155);
   //
   //
   
   //smoothing
   //
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
   //
   //

   //fft
   //
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
    delay(2000);
//    primary_loud = analogRead(0);

   black.hue = 0;
   black.sat = 0;
   black.val = 0;
   //
   //
}
 
 
void loop() 
{
   //fft
   //
 for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    
   //volume
   //
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
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
   //
   //
   
   //smoothing
   //
     // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = peak;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
 // Serial.println(average);
  delay(1); 
  //
  //
   
    
    // plotting
   Serial.println(map(peakToPeak, 1, 400  , 0, 255));
  //
  
   for(int j = 0; j < NUM_LEDS; j++){
   leds[j] = CHSV(map(average, 200, 1500, 0, 150), 255,  map(peakToPeak, 1, 400, 0, 255));
   }
   FastLED.show();
}
