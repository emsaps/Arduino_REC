#include <Adafruit_NeoPixel.h>

#define LED_PIN     6    // The pin connected to the LED strip
#define NUM_LEDS    78   // Number of LEDs in your strip
#define BUTTON_1    2    // Pin for the first button
#define BUTTON_2    3    // Pin for the second button
#define BUTTON_3    4    // Pin for the third button

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int currentState = -1;  // -1 represents the initial off state
int brightness = 0;
bool increasing = true;
bool stateChanged = false;

// Define colors
uint32_t OFF, WHITE, PALE_WHITE, GREEN, BLUE, RED, ORANGE;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);

  // Initialize colors
  OFF = strip.Color(0, 0, 0);
  WHITE = strip.Color(255, 255, 255);
  PALE_WHITE = strip.Color(128, 128, 128);
  GREEN = strip.Color(0, 255, 0);
  BLUE = strip.Color(0, 0, 255);
  RED = strip.Color(255, 0, 0);
  ORANGE = strip.Color(255, 165, 0);
}

void loop() {
  checkButtons();
  updateBrightness();
  updateLEDs();
  strip.show();
  delay(10); // Small delay to control the speed of brightness change
}

void checkButtons() {
  if (digitalRead(BUTTON_1) == LOW && currentState != 0) {
    currentState = 0;
    stateChanged = true;
  } else if (digitalRead(BUTTON_2) == LOW && currentState != 1) {
    currentState = 1;
    stateChanged = true;
  } else if (digitalRead(BUTTON_3) == LOW && currentState != 2) {
    currentState = 2;
    stateChanged = true;
  }

  if (stateChanged) {
    strip.clear();
    strip.show();
    delay(200); // Short delay to make the off state visible
    stateChanged = false;
    brightness = 0;
    increasing = true;
  }
}

void updateBrightness() {
  if (increasing) {
    brightness++;
    if (brightness >= 255) increasing = false;
  } else {
    brightness--;
    if (brightness <= 0) increasing = true;
  }
}

void updateLEDs() {
  switch (currentState) {
    case 0:
      setStateOne();
      break;
    case 1:
      setStateTwo();
      break;
    case 2:
      setStateThree();
      break;
    default:
      strip.clear(); // All LEDs off in the initial state
  }
}

void setStateOne() {
  setColor(0, 2, WHITE);
  setColor({6, 8, 10, 25, 26, 27, 28, 29, 33, 39, 40, 41, 77}, GREEN);
  setColor({8, 25, 27, 29, 33}, BLUE);
  setColor({12, 34, 35, 51}, OFF);
  setColor(35, RED);
}

void setStateTwo() {
  setColor(0, 2, PALE_WHITE);
  setColor({8, 25, 26, 27, 28, 29, 39, 41}, RED);
  setColor({27, 29}, BLUE);
  setColor({6, 10, 12, 33, 34, 35, 40, 51}, OFF);
  setColor(77, GREEN);
}

void setStateThree() {
  setColor(0, 2, ORANGE);
  setColor({6, 10, 25, 27, 29, 39, 41, 77}, BLUE);
  setColor({8, 12, 26, 28, 33, 35, 40, 51}, RED);
}

void setColor(int ledIndex, uint32_t color) {
  if (color == OFF) {
    strip.setPixelColor(ledIndex, OFF);
  } else {
    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >> 8);
    uint8_t b = (uint8_t)color;
    strip.setPixelColor(ledIndex, strip.Color(
      (r * brightness) / 255,
      (g * brightness) / 255,
      (b * brightness) / 255
    ));
  }
}

void setColor(int startLed, int endLed, uint32_t color) {
  for (int i = startLed; i <= endLed; i++) {
    setColor(i, color);
  }
}

void setColor(std::initializer_list<int> leds, uint32_t color) {
  for (int led : leds) {
    setColor(led, color);
  }
}