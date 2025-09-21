#include <Adafruit_NeoPixel.h>


#define LED_PIN     6    // The pin connected to the LED strip
#define NUM_LEDS    78   // Number of LEDs in your strip
#define BUTTON_1    2    // Pin for the first button
#define BUTTON_2    3    // Pin for the second button
#define BUTTON_3    4    // Pin for the third button

// Debounce settings
#define DEBOUNCE_DELAY 50 // ms


Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Enum for states
enum LedState {
  STATE_OFF = -1,
  STATE_ONE = 0,
  STATE_TWO = 1,
  STATE_THREE = 2
};

LedState currentState = STATE_OFF;
int brightness = 0;
bool increasing = true;
bool stateChanged = false;

// Debounce variables
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH;

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
  checkButtonsDebounced();
  updateBrightness();
  updateLEDs();
  strip.show();
  delay(10); // Small delay to control the speed of brightness change
}


// Debounced button check
void checkButtonsDebounced() {
  int reading1 = digitalRead(BUTTON_1);
  int reading2 = digitalRead(BUTTON_2);
  int reading3 = digitalRead(BUTTON_3);
  unsigned long now = millis();

  // Button 1
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = now;
  }
  if ((now - lastDebounceTime1) > DEBOUNCE_DELAY) {
    if (reading1 == LOW && currentState != STATE_ONE) {
      currentState = STATE_ONE;
      stateChanged = true;
    }
  }
  lastButtonState1 = reading1;

  // Button 2
  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = now;
  }
  if ((now - lastDebounceTime2) > DEBOUNCE_DELAY) {
    if (reading2 == LOW && currentState != STATE_TWO) {
      currentState = STATE_TWO;
      stateChanged = true;
    }
  }
  lastButtonState2 = reading2;

  // Button 3
  if (reading3 != lastButtonState3) {
    lastDebounceTime3 = now;
  }
  if ((now - lastDebounceTime3) > DEBOUNCE_DELAY) {
    if (reading3 == LOW && currentState != STATE_THREE) {
      currentState = STATE_THREE;
      stateChanged = true;
    }
  }
  lastButtonState3 = reading3;

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

// Update LEDs based on the current state
void updateLEDs() {
  switch (currentState) {
    case STATE_ONE:
      setStateOne();
      break;
    case STATE_TWO:
      setStateTwo();
      break;
    case STATE_THREE:
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

// Set color to a single LED, with brightness scaling (unless OFF)
void setColor(int ledIndex, uint32_t color) {
  if (color == OFF || brightness == 0) {
    strip.setPixelColor(ledIndex, OFF);
    return;
  }
  uint8_t r = (uint8_t)(color >> 16);
  uint8_t g = (uint8_t)(color >> 8);
  uint8_t b = (uint8_t)color;
  strip.setPixelColor(ledIndex, strip.Color(
    (r * brightness) / 255,
    (g * brightness) / 255,
    (b * brightness) / 255
  ));
}

// Set color to a range of LEDs
void setColor(int startLed, int endLed, uint32_t color) {
  for (int i = startLed; i <= endLed; i++) {
    setColor(i, color);
  }
}

// Set color to a list of LEDs
void setColor(std::initializer_list<int> leds, uint32_t color) {
  for (int led : leds) {
    setColor(led, color);
  }
}