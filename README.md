# DormLights
> Arduino/NodeMCU/ESP8266 program that combines both amplitude and frequency of an audio track into a "Lit AF" package.

### freq_and_vol.ino
This program takes input from the microphone and processes it with arduinoFFT, FastLED, and the Adafruit Volume calculations. The color of the lights displays peak frequency data while the brightness is shown with volume.
### vol_from_center.ino
This program takes input from the microphone and processes it with FastLED and the Adafruit Volume calculations. The lights display from the center with the length and color dictated by peak volume levels.

## Installation

Arduino/NodeMCU/ESP8266:

```
git clone https://github.com/michaelpeterswa/DormLights.git
```
Or download the file manually.
Download up-to-date Arduino IDE and sync FastLED and arduinoFFT libraries.
Open in Arduino IDE, compile, and flash board

## Release History

* 0.1
    * First complete release (07.19.18)

## Meta

Michael Peters – michael@michaelpeterswa.com

Distributed under the MIT license. See ``LICENSE`` for more information.

[https://github.com/michaelpeterswa](https://github.com/michaelpeterswa)
