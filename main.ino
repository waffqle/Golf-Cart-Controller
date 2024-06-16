#include "InputDebounce.h"

// Debounce setup
#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

// Setup pins for control buttons
#define PIN_MISC      4
#define PIN_SOUND     5
#define PIN_LIGHTS    6
#define PIN_DIRECTION 7

// Setup pins for the relay board
#define PIN_MISC_RELAY      4
#define PIN_SOUND_RELAY     5
#define PIN_LIGHTS_RELAY    6
#define PIN_DIRECTION_RELAY 7


void setup() {
  // Setup pull ups 
  // Buttons
  pinMode(PIN_MISC,       INPUT_PULLUP)
  pinMode(PIN_SOUND,      INPUT_PULLUP)
  pinMode(PIN_LIGHTS,     INPUT_PULLUP)
  pinMode(PIN_DIRECTION,  INPUT_PULLUP)
  // Relays
  pinMode(PIN_MISC_RELAY,       INPUT_PULLUP)
  pinMode(PIN_SOUND_RELAY,      INPUT_PULLUP)
  pinMode(PIN_LIGHTS_RELAY,     INPUT_PULLUP)
  pinMode(PIN_DIRECTION_RELAY,  INPUT_PULLUP)
}

void loop() {
  // put your main code here, to run repeatedly:

}
