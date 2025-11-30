#include <Adafruit_NeoPixel.h>
#define LED_PIN 8
#define BUTTON1_PIN 6
#define BUTTON2_PIN 4
#define BUTTON3_PIN 2
#define NUM_LEDS 90

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int ledState1 = 0;  // State_1 for configuration LEDs (0: off, 1: on with colors)
int ledState2 = 0;  // State_2 for configuration LEDs (0: off, 1: on with colors)
int ledState3 = 0;  // State_3 for configuration LEDs (0: off, 1: on with colors)

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
}

void loop() {
  int buttonState1 = digitalRead(BUTTON1_PIN);
  int buttonState2 = digitalRead(BUTTON2_PIN);
  int buttonState3 = digitalRead(BUTTON3_PIN);

  // mezzogiorno, produzione fotovoltaica max
  if (buttonState1 == LOW) {
    // If Button 1 is pressed, toggle the state of LEDs
    ledState1 = 1 - ledState1;  // Toggle between 0 and 1
    if (ledState1 == 1) {
      // If LEDs are turned on, set their colors
      strip.setPixelColor(0, strip.Color(255, 255, 255));  // cabina primaria
      strip.setPixelColor(1, strip.Color(255, 255, 255));  //
      strip.setPixelColor(2, strip.Color(255, 255, 255));  //

      strip.setPixelColor(6, strip.Color(0, 255, 0));   // casa fotovoltaico
      strip.setPixelColor(8, strip.Color(0, 0, 255));   // casa
      strip.setPixelColor(10, strip.Color(0, 255, 0));  // casa fotovoltaico
      strip.setPixelColor(12, strip.Color(0, 0, 0));    // casa

      strip.setPixelColor(25, strip.Color(0, 0, 255));  // fabbrica/ospedale fotovoltaico
      strip.setPixelColor(26, strip.Color(0, 255, 0));  //
      strip.setPixelColor(27, strip.Color(0, 0, 255));  //
      strip.setPixelColor(28, strip.Color(0, 255, 0));  //
      strip.setPixelColor(29, strip.Color(0, 0, 255));  //

      strip.setPixelColor(33, strip.Color(0, 0, 255));  // ufficio
      strip.setPixelColor(34, strip.Color(0, 0, 0));    //
      strip.setPixelColor(35, strip.Color(255, 0, 0));  //

      strip.setPixelColor(39, strip.Color(0, 255, 0));  // condominio fotovoltaico
      strip.setPixelColor(40, strip.Color(0, 255, 0));  //
      strip.setPixelColor(41, strip.Color(0, 255, 0));  //

      strip.setPixelColor(51, strip.Color(0, 0, 0));  // casa

      strip.setPixelColor(77, strip.Color(0, 255, 0));  // casa montagna fotovoltaico
    }
    strip.show();  // Update the strip to display the new colors
  }


  // notte, preferibile utilizzo della rete elettrica nazionale per il basso costo dell'energia a causa della non possibilità di spegnimento degli impianti termoelettrici
  if (buttonState2 == LOW) {
    // If Button 1 is pressed, toggle the state of LEDs
    ledState2 = 1 - ledState2;  // Toggle between 0 and 1
    if (ledState2 == 1) {
      // If LEDs are turned on, set their colors
      strip.setPixelColor(0, strip.Color(1, 1, 1));  // cabina primaria
      strip.setPixelColor(1, strip.Color(1, 1, 1));  //
      strip.setPixelColor(2, strip.Color(1, 1, 1));  //

      strip.setPixelColor(6, strip.Color(0, 0, 0));    // casa fotovoltaico
      strip.setPixelColor(8, strip.Color(255, 0, 0));  // casa
      strip.setPixelColor(10, strip.Color(0, 0, 0));   // casa fotovoltaico
      strip.setPixelColor(12, strip.Color(0, 0, 0));   // casa

      strip.setPixelColor(25, strip.Color(255, 0, 0));  // fabbrica/ospedale fotovoltaico
      strip.setPixelColor(26, strip.Color(0, 0, 255));  //
      strip.setPixelColor(27, strip.Color(255, 0, 0));  //
      strip.setPixelColor(28, strip.Color(0, 0, 255));  //
      strip.setPixelColor(29, strip.Color(255, 0, 0));  //

      strip.setPixelColor(33, strip.Color(0, 0, 0));  // ufficio
      strip.setPixelColor(34, strip.Color(0, 0, 0));  //
      strip.setPixelColor(35, strip.Color(0, 0, 0));  //

      strip.setPixelColor(39, strip.Color(255, 0, 0));  // condominio fotovoltaico
      strip.setPixelColor(40, strip.Color(0, 0, 0));    //
      strip.setPixelColor(41, strip.Color(255, 0, 0));  //

      strip.setPixelColor(51, strip.Color(0, 0, 0));  // casa

      strip.setPixelColor(77, strip.Color(0, 0, 255));  // casa montagna fotovoltaico
    }
    strip.show();  // Update the strip to display the new colors
  }


  // ore di punta 07:00, 19:00. produzione fotovoltaica quasi nulla. necessità di accumulatori già carichi per ridurre il picco di assorbimento dalla rete nazionale (spesso energia fossile)
  if (buttonState3 == LOW) {
    // If Button 1 is pressed, toggle the state of LEDs
    ledState3 = 1 - ledState3;  // Toggle between 0 and 1
    if (ledState3 == 1) {
      // If LEDs are turned on, set their colors
      strip.setPixelColor(0, strip.Color(255, 153, 0));  // cabina primaria
      strip.setPixelColor(1, strip.Color(255, 153, 0));  //
      strip.setPixelColor(2, strip.Color(255, 153, 0));  //

      strip.setPixelColor(6, strip.Color(0, 0, 255));   // casa fotovoltaico
      strip.setPixelColor(8, strip.Color(255, 0, 0));   // casa
      strip.setPixelColor(10, strip.Color(0, 0, 255));  // casa fotovoltaico
      strip.setPixelColor(12, strip.Color(255, 0, 0));  // casa

      strip.setPixelColor(25, strip.Color(255, 0, 0));  // fabbrica/ospedale fotovoltaico
      strip.setPixelColor(26, strip.Color(0, 0, 255));  //
      strip.setPixelColor(27, strip.Color(255, 0, 0));  //
      strip.setPixelColor(28, strip.Color(0, 0, 255));  //
      strip.setPixelColor(29, strip.Color(255, 0, 0));  //

      strip.setPixelColor(33, strip.Color(255, 0, 0));  // ufficio
      strip.setPixelColor(34, strip.Color(0, 0, 255));  //
      strip.setPixelColor(35, strip.Color(255, 0, 0));  //

      strip.setPixelColor(39, strip.Color(0, 0, 255));  // condominio fotovoltaico
      strip.setPixelColor(40, strip.Color(255, 0, 0));  //
      strip.setPixelColor(41, strip.Color(0, 0, 255));  //

      strip.setPixelColor(51, strip.Color(255, 0, 0));  // casa

      strip.setPixelColor(77, strip.Color(0, 0, 255));  // casa montagna fotovoltaico
    }
    strip.show();  // Update the strip to display the new colors
  }
}