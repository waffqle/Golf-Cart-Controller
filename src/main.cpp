#include <Arduino.h>
#include "InputDebounce.h"
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

// Control Buttons
#define PIN_MISC      0
#define PIN_SOUND     1
#define PIN_LIGHTS    2
#define PIN_DIRECTION 3
// Relay Board
#define PIN_MISC_RELAY      4
#define PIN_SOUND_RELAY     5
#define PIN_LIGHTS_RELAY    6
#define PIN_DIRECTION_RELAY 7
// LCD
hd44780_I2Cexp lcd(0x27); // declare lcd object: auto locate & auto config expander chip

// Debounce setup
#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

static InputDebounce buttonDirection; // Forward & Reverse toggle
static InputDebounce buttonLights;    // Headlights
static InputDebounce buttonSound;     // Stereo
static InputDebounce buttonMisc;      // Whatever you want

bool going_forward = false;

void togglePin(uint8_t pin){
  digitalWrite(pin, !digitalRead(pin));
}

void buttonDirection_pressed(uint8_t pinIn){
  Serial.println("Direction pressed");
  togglePin(PIN_DIRECTION_RELAY);
}

void buttonLights_pressed(uint8_t pinIn){
  Serial.println("Lights pressed");
  togglePin(PIN_LIGHTS_RELAY);
}

void buttonSound_pressed(uint8_t pinIn){
  Serial.println("Sound pressed");
  togglePin(PIN_SOUND_RELAY);
}

void buttonMisc_pressed(uint8_t pinIn){
  Serial.println("Misc pressed");
  togglePin(PIN_MISC_RELAY);
}

void setup() {
	// Turn on the blacklight and print a message.
  int status = lcd.begin(20,4);
  if(status) // non zero status means it was unsuccesful
	{
		// begin() failed so blink error code using the onboard LED if possible
		hd44780::fatalError(status); // does not return
	}
	
  lcd.setCursor(0,0);
  lcd.print("Direction:");
  lcd.setCursor(0,1);
  lcd.print("Stereo:");
  lcd.setCursor(0,2);
  lcd.print("Lights:");
  lcd.setCursor(0,3);
  lcd.print("Battery %:");

  // Setup pull ups 
  // Relays
  pinMode(PIN_MISC_RELAY,       OUTPUT);
  pinMode(PIN_SOUND_RELAY,      OUTPUT);
  pinMode(PIN_LIGHTS_RELAY,     OUTPUT);
  pinMode(PIN_DIRECTION_RELAY,  OUTPUT);

  // register callback functions (shared, used by all buttons)
  buttonDirection.registerCallbacks(buttonDirection_pressed,  NULL, NULL, NULL);
  buttonLights.registerCallbacks(buttonLights_pressed,        NULL, NULL, NULL);
  buttonSound.registerCallbacks(buttonSound_pressed,          NULL, NULL, NULL);
  buttonMisc.registerCallbacks(buttonMisc_pressed,            NULL, NULL, NULL);

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