#include <Adafruit_CircuitPlayground.h>
#define TOTAL 20
#define CAPTURE_MILLISECONDS 50
#define COLOUR_SHIFT_SECONDS 2


void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(255);
  CircuitPlayground.clearPixels();
  seedRandom();
}

uint8_t samples[TOTAL];
uint8_t counter = 0;
float averagePressure = 0;
uint8_t rgbGoals[3];
float rgbCurrent[3];
float rgbShift[3];

void loop() {
  // Generating random colours
  // If the current colours have all met their goals
  if ((uint8_t)round(rgbCurrent[0]) == rgbGoals[0] && (uint8_t)round(rgbCurrent[1]) == rgbGoals[1] && (uint8_t)round(rgbCurrent[2]) == rgbGoals[2]) {
    // Generate random numbers from 0 to 255 for R, G and B
    for (int i = 0; i < 3; i++) {
      rgbGoals[i] = (uint8_t)rand() % 256;
    }
    for (int i = 0; i < 3; i++) {
      // Calculate the amount needed to shift uniformly every time a new sound pressure is captured, which is what the loop hangs on, for each colour
      rgbShift[i] = (rgbGoals[i] - rgbCurrent[i]) / ((COLOUR_SHIFT_SECONDS * 1000) / CAPTURE_MILLISECONDS);
    }
  }

  //Shifting current colours
  for (int i = 0; i < 3; i++) {
    rgbCurrent[i] += rgbShift[i];
  }

  // Capturing sound pressure and updating the running average to acclimate to current noise levels
  float currentPressure = CircuitPlayground.mic.soundPressureLevel(CAPTURE_MILLISECONDS);
  samples[counter] = (uint8_t)currentPressure;
  counter++;
  counter = counter % TOTAL;
  int sampleTotal = 0;
  for (int i = 0; i < TOTAL; i++) {
    sampleTotal += samples[i];
  }
  uint8_t sampleAverage = sampleTotal / TOTAL;


  if (currentPressure > sampleAverage + 5) {
    uint8_t brightness = (uint8_t)(currentPressure - sampleAverage);
    CircuitPlayground.strip.setBrightness(brightness);
  }
  else {
    CircuitPlayground.strip.setBrightness(0);
  }
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.strip.setPixelColor(i, (uint8_t)rgbCurrent[0], (uint8_t)rgbCurrent[1], (uint8_t)rgbCurrent[2]);
  }
  CircuitPlayground.strip.show();
}

void seedRandom(){
  delay(100);
  int analog1 = analogRead(A0);
  int analog2 = analogRead(A4);
  int analog3 = analogRead(A5);
  int analog4 = analogRead(A7);
  int analog5 = analogRead(A9);
  int analog6 = analogRead(A10);
  int analog7 = analogRead(A11);
  srand(analog1 * analog2 * analog3 * analog4 * analog5 * analog6 * analog7);
}
