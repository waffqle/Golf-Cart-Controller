#include <Arduino.h>
#include "InputDebounce.h"

// Debounce setup
#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

// Setup pins for control buttons
#define PIN_MISC      0
#define PIN_SOUND     1
#define PIN_LIGHTS    2
#define PIN_DIRECTION 3

// Setup pins for the relay board
#define PIN_MISC_RELAY      4
#define PIN_SOUND_RELAY     5
#define PIN_LIGHTS_RELAY    6
#define PIN_DIRECTION_RELAY 7

static InputDebounce buttonDirection; // Forward & Reverse toggle
static InputDebounce buttonLights;    // Headlights
static InputDebounce buttonSound;     // Stereo
static InputDebounce buttonMisc;      // Whatever you want


void buttonDirection_pressed(uint8_t pinIn){
  Serial.println("Direction pressed");
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void buttonLights_pressed(uint8_t pinIn){
  Serial.println("Lights pressed");
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void buttonSound_pressed(uint8_t pinIn){
  Serial.println("Sound pressed");
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void buttonMisc_pressed(uint8_t pinIn){
  Serial.println("Misc pressed");
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void button_releasedCallback(uint8_t pinIn){}
void button_pressedDurationCallback(uint8_t pinIn, unsigned long duration){}
void button_releasedDurationCallback(uint8_t pinIn, unsigned long duration){}

void setup() {
  // Debug messages
  Serial.begin(9600);  
  Serial.println("Here we go");

  // LED for blinking!
  pinMode(LED_BUILTIN, OUTPUT);

  // Setup pull ups 
  // Relays
  pinMode(PIN_MISC_RELAY,       INPUT_PULLUP);
  pinMode(PIN_SOUND_RELAY,      INPUT_PULLUP);
  pinMode(PIN_LIGHTS_RELAY,     INPUT_PULLUP);
  pinMode(PIN_DIRECTION_RELAY,  INPUT_PULLUP);

  // register callback functions (shared, used by all buttons)
  buttonDirection.registerCallbacks(buttonDirection_pressed,  button_releasedCallback, button_pressedDurationCallback, button_releasedDurationCallback);
  buttonLights.registerCallbacks(buttonLights_pressed,        button_releasedCallback, button_pressedDurationCallback, button_releasedDurationCallback);
  buttonSound.registerCallbacks(buttonSound_pressed,          button_releasedCallback, button_pressedDurationCallback, button_releasedDurationCallback);
  buttonMisc.registerCallbacks(buttonMisc_pressed,            button_releasedCallback, button_pressedDurationCallback, button_releasedDurationCallback);

  // setup input buttons (debounced)
  buttonDirection.setup(PIN_DIRECTION,  BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
  buttonLights.setup(PIN_LIGHTS,        BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
  buttonSound.setup(PIN_SOUND,          BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);
  buttonMisc.setup(PIN_MISC,            BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);  
}

void loop() {
  // Look for button presses!
  unsigned long now = millis();

  buttonDirection.process(now);
  buttonLights.process(now);
  buttonSound.process(now);
  buttonMisc.process(now);
  
  delay(1);
}