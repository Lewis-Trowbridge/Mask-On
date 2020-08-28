#include <Adafruit_CircuitPlayground.h>
#define TOTAL 20


void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(255);
  CircuitPlayground.clearPixels();
  Serial.begin(9600);
  if (!Serial){
    
  }
}

uint8_t samples[TOTAL];
uint8_t counter = 0;
float averagePressure = 0;
  uint8_t r = 68;
  uint8_t g = 92;
  uint8_t b = 171;

void loop() {
  // put your main code here, to run repeatedly:
  float currentPressure = CircuitPlayground.mic.soundPressureLevel(50);
  samples[counter] = (uint8_t)currentPressure;
  counter++;
  counter = counter % TOTAL;
  int sampleTotal = 0;
  for (int i = 0; i < TOTAL; i++){
    sampleTotal += samples[i];
  }
  uint8_t sampleAverage = sampleTotal / TOTAL;
  if (currentPressure > sampleAverage + 10){
    uint8_t brightness = (uint8_t)(currentPressure - sampleAverage);
    CircuitPlayground.strip.setBrightness(brightness);
  }
  else {
    CircuitPlayground.strip.setBrightness(0);
  }
  for (int i=0; i<10; i++){
    CircuitPlayground.strip.setPixelColor(i, r, g, b);
  }
  CircuitPlayground.strip.show();
  
}
