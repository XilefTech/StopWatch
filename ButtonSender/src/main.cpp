#include <Arduino.h>
#include "wifiFunctions.h"
#include "config.h"

bool buttonPressed = false; // Flag to indicate if the button is pressed

void IRAM_ATTR onButtonPress() {
	buttonPressed = true; // Set the flag when the button is pressed
}

void setup() {
	initWifi();

	pinMode(config::buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
	attachInterrupt(config::buttonPin, onButtonPress, FALLING); // Attach interrupt to button pin
}

void loop() {
	if (buttonPressed) { // Check if the button was pressed
		buttonPressed = false; // Reset the flag

		// Send a message to the server (replace with your server's IP and port)
		sendMessage("Button Pressed!"); // Send message to server
	}
}