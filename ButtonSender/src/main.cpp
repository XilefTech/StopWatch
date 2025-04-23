#include "Communication.h"
#include "battery.h"

bool buttonPressed = false;
bool buttonReleased = false;
int previouslySentBatteryLevel = 999;


void IRAM_ATTR onButtonPress() {
	buttonPressed = true;
}

void IRAM_ATTR onButtonRelease() {
	buttonReleased = true;
}

String hostMac = "";
Communication comms;

void setup() {
	pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as output
	digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED to indicate setup is in progress

	comms.initWifi();

	pinMode(config::buttonPin, INPUT_PULLUP); // Set button pin as input with pull-up resistor
	attachInterrupt(config::buttonPin, onButtonPress, RISING); // Attach interrupt to button pin
	attachInterrupt(config::buttonPin, onButtonPress, FALLING); // Attach interrupt to button pin

	// flash the LED to indicate setup is complete
	for (int i = 0; i < 3; i++) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
	}
	digitalWrite(LED_BUILTIN, LOW); // Turn off the LED to indicate setup is complete
}

void loop() {
	if (buttonPressed) { // Check if the button was pressed
		buttonPressed = false; // Reset the flag

		comms.sendPress(); // Send message to server

		if (!buttonReleased) { // we do not want to wait now if we want to send smth else that is time-critical
			delay(100); // Delay to avoid multiple presses being registered
		}	
	}

	if (buttonReleased) { // Check if the button was pressed
		buttonReleased = false; // Reset the flag

		comms.sendRelease(); // Send message to server
		delay(100); // Delay to avoid multiple presses being registered
	}

	// check battery level, only send updates if the battery level has changed significantly to save battery life
	uint8_t batteryLevel = getBatteryPercent(); // Get the current battery level
	if (previouslySentBatteryLevel - batteryLevel >= config::battery::transmissionThreshold) { // Check if the battery level has changed
		previouslySentBatteryLevel = batteryLevel; // Update the previous battery level

		comms.sendBatteryUpdate(batteryLevel); // Send battery status to server
	}
}