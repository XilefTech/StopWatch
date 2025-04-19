#include <Arduino.h>
#include "wifiFunctions.h"
#include "battery.h"

bool buttonPressed = false; // Flag to indicate if the button is pressed
int previouslySentBatteryLevel = 999; // Variable to store the previous battery level


void IRAM_ATTR onButtonPress() {
	buttonPressed = true; // Set the flag when the button is pressed
}


void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as output
	digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED to indicate setup is in progress

	initWifi();

	pinMode(config::buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
	attachInterrupt(config::buttonPin, onButtonPress, RISING); // Attach interrupt to button pin

	// flash the LED to indicate setup is complete
	for (int i = 0; i < 3; i++) {
		digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
		delay(100); // Wait for 100 ms
		digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
		delay(100); // Wait for 100 ms
	}
	digitalWrite(LED_BUILTIN, LOW); // Turn off the LED to indicate setup is complete
}

void loop() {
	if (buttonPressed) { // Check if the button was pressed
		buttonPressed = false; // Reset the flag

		sendPress(); // Send message to server
	}

	// check battery level, only send updates if the battery level has changed significantly to save battery life
	int batteryLevel = getBatteryPercent(); // Get the current battery level
	if (previouslySentBatteryLevel - batteryLevel >= config::battery::transmissionThreshold) { // Check if the battery level has changed
		previouslySentBatteryLevel = batteryLevel; // Update the previous battery level

		sendBatteryUpdate(batteryLevel); // Send battery status to server
	}
}