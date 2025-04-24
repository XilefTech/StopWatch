#include "Communication.h"
#include "battery.h"
#include <Ascii-print.h>

#include <Bounce2.h>

Bounce2::Button button = Bounce2::Button();

int previouslySentBatteryLevel = 999;


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

	button.attach(config::buttonPin, INPUT_PULLUP);
	button.interval(config::debounceTime);
	button.setPressedState(HIGH);

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
	button.update();

	if (button.pressed()) {
		comms.sendPress();
	} else if (button.released()) {
		comms.sendRelease();
	}

	// check battery level, only send updates if the battery level has changed significantly to save battery life
	uint8_t batteryLevel = getBatteryPercent(); // Get the current battery level
	if (previouslySentBatteryLevel - batteryLevel >= config::battery::transmissionThreshold) { // Check if the battery level has changed
		previouslySentBatteryLevel = batteryLevel; // Update the previous battery level

		comms.sendBatteryUpdate(batteryLevel); // Send battery status to server
	}
}