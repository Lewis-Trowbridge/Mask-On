#include <Adafruit_CircuitPlayground.h>
#define TOTAL 20
#define CAPTURE_MILLISECONDS 50
#define COLOUR_SHIFT_SECONDS 2


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
uint8_t rGoal = 0;
uint8_t gGoal = 0;
uint8_t bGoal = 0;
float rCurrent = 0;
float gCurrent = 0;
float bCurrent = 0;

void loop() {
  // Generating random colours 

  
  // Capturing sound pressure and updating the running average to acclimate to current noise levels
  float currentPressure = CircuitPlayground.mic.soundPressureLevel(CAPTURE_MILLISECONDS);
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
    CircuitPlayground.strip.setPixelColor(i, (uint8_t)rCurrent, (uint8_t)gCurrent, (uint8_t)bCurrent);
  }
  CircuitPlayground.strip.show();
  
}
