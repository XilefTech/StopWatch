#include "Communication.h"
#include "battery.h"
#include <Ascii-print.h>

bool buttonPressed = false;
bool buttonReleased = false;
int previouslySentBatteryLevel = 999;


uint64_t lastPressTime = 0;

void IRAM_ATTR onButtonChange() {
	bool buttonState = digitalRead(config::buttonPin);

	if (millis() - lastPressTime < 100) { // Debounce time of 50ms
		return;
	}

	if (buttonState) {
		buttonReleased = true;
	} else {
		buttonPressed = true;
	}
	lastPressTime = millis(); // Update the last press time
}

String hostMac = "";
Communication comms;

void setup() {
	Serial.begin(115200);
	Serial.println("Welcome to \n");
	Serial.println(ascii_print::stopWatch);
	Serial.println("ButtonSender - ESP32\n");
	Serial.println("Starting up...");
	
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	comms.initWifi();

	pinMode(config::buttonPin, INPUT_PULLUP);
	attachInterrupt(config::buttonPin, onButtonChange, CHANGE);

	// flash the LED to indicate setup is complete
	for (int i = 0; i < 3; i++) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
	}
	digitalWrite(LED_BUILTIN, LOW); // Turn off the LED to indicate setup is complete
	Serial.println("Startup complete.");
}

void loop() {
	if (buttonPressed) {
		comms.sendPress();

		if (!buttonReleased) { // we do not want to wait now if we want to send smth else that is time-critical
			delay(100); // Delay to avoid multiple presses being registered
		}
		buttonPressed = false;
	}

	if (buttonReleased) { 
		comms.sendRelease();
		delay(200); // Delay to avoid multiple presses being registered
		buttonReleased = false; 
	}

	// check battery level, only send updates if the battery level has changed significantly to save battery life
	uint8_t batteryLevel = getBatteryPercent(); // Get the current battery level
	if (previouslySentBatteryLevel - batteryLevel >= config::battery::transmissionThreshold) { // Check if the battery level has changed
		previouslySentBatteryLevel = batteryLevel; // Update the previous battery level

		comms.sendBatteryUpdate(batteryLevel); // Send battery status to server
	}
}