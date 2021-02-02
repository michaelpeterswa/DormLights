//#define ESPALEXA_DEBUG

#include <ESP8266WiFi.h>
#include <Espalexa.h>
#include <WS2812FX.h>

#define NUMLEDS 150 // number of LEDs on the strip
#define DATAPIN  14 // GPIO pin used to drive the LED strip

#define WIFI_SSID     "" // WiFi network
#define WIFI_PASSWORD "" // WiFi network password

/* 
 *  define your ws2812fx presets
 */
//WS2812FX::segment purple_preset[MAX_NUM_SEGMENTS] = {
//  // { first, last, speed, mode, options, colors[] }
//  {0, NUMLEDS-1, 5000, FX_MODE_STATIC, NO_OPTIONS, {PURPLE}}
//};
//
//WS2812FX::segment white_preset[MAX_NUM_SEGMENTS] = {
//  // { first, last, speed, mode, options, colors[] }
//  {0, NUMLEDS-1, 5000, FX_MODE_STATIC, NO_OPTIONS, {WHITE}}
//};
//
//WS2812FX::segment rainbow_preset[MAX_NUM_SEGMENTS] = {
//  // { first, last, speed, mode, options, colors[] }
//  {0, NUMLEDS-1, 5000, FX_MODE_RAINBOW_CYCLE, NO_OPTIONS, {PURPLE}}
//};

WS2812FX::segment fire_preset[MAX_NUM_SEGMENTS] = {
  // { first, last, speed, mode, options, colors[] }
  {0, NUMLEDS-1, 5000, FX_MODE_FIRE_FLICKER_SOFT, NO_OPTIONS, {ORANGE, RED}}
};
WS2812FX::segment ice_preset[MAX_NUM_SEGMENTS] = {
  // { first, last, speed, mode, options, colors[] }
  {0, NUMLEDS-1, 5000, FX_MODE_SPARKLE, NO_OPTIONS, {0x00C0AA, 0x96E7FF}}
};

Espalexa espalexa;
WS2812FX ws2812fx = WS2812FX(NUMLEDS, DATAPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("\r\n");

  // init WiFi
  WiFi.hostname("DormLights");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to " WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nServer IP is ");
  Serial.println(WiFi.localIP());

  // add your alexa virtual devices giving them a name and associated callback
//  espalexa.addDevice("L E D lights", ledCallback);
//  espalexa.addDevice("purple lights", purpleCallback);
//  espalexa.addDevice("white lights", whiteCallback);
//  espalexa.addDevice("rainbow lights", rainbowCallback);
  espalexa.addDevice("fire lights", fireCallback);
  espalexa.addDevice("ice lights", iceCallback);
  espalexa.begin();

  ws2812fx.init();
  ws2812fx.stop(); // ws2812fx is stopped until it receives a command from Alexa 
}
 
void loop() {
   espalexa.loop();
   ws2812fx.service();
   delay(1);
}


/*
 * our callback functions
 */
//void ledCallback(uint8_t brightness) { // used for on, off or adjusting brightness without changing the active preset
//  Serial.print("Loading led ");
//  Serial.println(brightness);
//  loadPreset(NULL, brightness);
//}
//
//void purpleCallback(uint8_t brightness) {
//  Serial.print("Loading color preset ");Serial.println(brightness);
//  loadPreset(purple_preset, brightness);
//}
//
//void whiteCallback(uint8_t brightness) {
//  Serial.print("Loading color preset ");Serial.println(brightness);
//  loadPreset(white_preset, brightness);
//}
//
//void rainbowCallback(uint8_t brightness) {
//  Serial.print("Loading color preset ");Serial.println(brightness);
//  loadPreset(rainbow_preset, brightness);
//}

void fireCallback(uint8_t brightness) {
  Serial.print("Loading color preset ");
  Serial.println(brightness);
  loadPreset(fire_preset, brightness);
}
void iceCallback(uint8_t brightness) {
  Serial.print("Loading color preset ");
  Serial.println(brightness);
  loadPreset(ice_preset, brightness);
}
/*
 * function loads and runs the specified ws2812fx preset
 */
void loadPreset(WS2812FX::segment segments[], uint8_t brightness) {
  ws2812fx.stop();
  if(brightness == 0) return;

  if(segments != NULL) {
    ws2812fx.resetSegments();
    for(int i=0; i<MAX_NUM_SEGMENTS; i++) {
      WS2812FX::segment seg = segments[i];
      if(i != 0 && seg.start == 0) break;
      ws2812fx.setSegment(i, seg.start, seg.stop, seg.mode, seg.colors, seg.speed, seg.options);
    }
  }

  ws2812fx.setBrightness(brightness);
  ws2812fx.start();
}
