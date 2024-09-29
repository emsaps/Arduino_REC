#include <Adafruit_NeoPixel.h>

#define LED_PIN 8
#define BUTTON1_PIN 6
#define BUTTON2_PIN 4
#define BUTTON3_PIN 2
#define NUM_LEDS 90

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// LED states
int ledState1 = 0;
int ledState2 = 0;
int ledState3 = 0;

// Color definitions
const uint32_t COLOR_WHITE = strip.Color(255, 255, 255);
const uint32_t COLOR_GREEN = strip.Color(0, 255, 0);
const uint32_t COLOR_BLUE = strip.Color(0, 0, 255);
const uint32_t COLOR_RED = strip.Color(255, 0, 0);
const uint32_t COLOR_ORANGE = strip.Color(255, 153, 0);
const uint32_t COLOR_DIM_WHITE = strip.Color(1, 1, 1);
const uint32_t COLOR_OFF = strip.Color(0, 0, 0);

// Debounce variables
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long debounceDelay = 50;

void setup() {
  strip.begin();
  strip.show();
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
}

void setLEDs1() {
  strip.setPixelColor(0, COLOR_WHITE);
  strip.setPixelColor(1, COLOR_WHITE);
  strip.setPixelColor(2, COLOR_WHITE);
  strip.setPixelColor(6, COLOR_GREEN);
  strip.setPixelColor(8, COLOR_BLUE);
  strip.setPixelColor(10, COLOR_GREEN);
  strip.setPixelColor(12, COLOR_OFF);
  strip.setPixelColor(25, COLOR_BLUE);
  strip.setPixelColor(26, COLOR_GREEN);
  strip.setPixelColor(27, COLOR_BLUE);
  strip.setPixelColor(28, COLOR_GREEN);
  strip.setPixelColor(29, COLOR_BLUE);
  strip.setPixelColor(33, COLOR_BLUE);
  strip.setPixelColor(34, COLOR_OFF);
  strip.setPixelColor(35, COLOR_RED);
  strip.setPixelColor(39, COLOR_GREEN);
  strip.setPixelColor(40, COLOR_GREEN);
  strip.setPixelColor(41, COLOR_GREEN);
  strip.setPixelColor(51, COLOR_OFF);
  strip.setPixelColor(77, COLOR_GREEN);
  strip.show();
}

void setLEDs2() {
  strip.setPixelColor(0, COLOR_DIM_WHITE);
  strip.setPixelColor(1, COLOR_DIM_WHITE);
  strip.setPixelColor(2, COLOR_DIM_WHITE);
  strip.setPixelColor(6, COLOR_OFF);
  strip.setPixelColor(8, COLOR_RED);
  strip.setPixelColor(10, COLOR_OFF);
  strip.setPixelColor(12, COLOR_OFF);
  strip.setPixelColor(25, COLOR_RED);
  strip.setPixelColor(26, COLOR_BLUE);
  strip.setPixelColor(27, COLOR_RED);
  strip.setPixelColor(28, COLOR_BLUE);
  strip.setPixelColor(29, COLOR_RED);
  strip.setPixelColor(33, COLOR_OFF);
  strip.setPixelColor(34, COLOR_OFF);
  strip.setPixelColor(35, COLOR_OFF);
  strip.setPixelColor(39, COLOR_RED);
  strip.setPixelColor(40, COLOR_OFF);
  strip.setPixelColor(41, COLOR_RED);
  strip.setPixelColor(51, COLOR_OFF);
  strip.setPixelColor(77, COLOR_BLUE);
  strip.show();
}

void setLEDs3() {
  strip.setPixelColor(0, COLOR_ORANGE);
  strip.setPixelColor(1, COLOR_ORANGE);
  strip.setPixelColor(2, COLOR_ORANGE);
  strip.setPixelColor(6, COLOR_BLUE);
  strip.setPixelColor(8, COLOR_RED);
  strip.setPixelColor(10, COLOR_BLUE);
  strip.setPixelColor(12, COLOR_RED);
  strip.setPixelColor(25, COLOR_RED);
  strip.setPixelColor(26, COLOR_BLUE);
  strip.setPixelColor(27, COLOR_RED);
  strip.setPixelColor(28, COLOR_BLUE);
  strip.setPixelColor(29, COLOR_RED);
  strip.setPixelColor(33, COLOR_RED);
  strip.setPixelColor(34, COLOR_BLUE);
  strip.setPixelColor(35, COLOR_RED);
  strip.setPixelColor(39, COLOR_BLUE);
  strip.setPixelColor(40, COLOR_RED);
  strip.setPixelColor(41, COLOR_BLUE);
  strip.setPixelColor(51, COLOR_RED);
  strip.setPixelColor(77, COLOR_BLUE);
  strip.show();
}

void toggleLEDs(int &ledState, void (*setLEDs)(), unsigned long &lastDebounceTime, int buttonPin) {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    ledState = 1 - ledState;
    if (ledState == 1) {
      setLEDs();
    } else {
      strip.clear();
      strip.show();
    }
  }
}

void loop() {
  toggleLEDs(ledState1, setLEDs1, lastDebounceTime1, BUTTON1_PIN);
  toggleLEDs(ledState2, setLEDs2, lastDebounceTime2, BUTTON2_PIN);
  toggleLEDs(ledState3, setLEDs3, lastDebounceTime3, BUTTON3_PIN);
}
