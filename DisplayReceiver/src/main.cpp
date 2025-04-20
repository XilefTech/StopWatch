#include <Arduino.h>
#include <display.h>
#include <timer.h>


Timer* timer = nullptr;

void setup() {
	Serial.begin(115200);
	Serial.println("Starting up...");

	initDisplay(100); // Initialize the display

	timer = new Timer(5, 7, display); // Create a timer object with the display
	timer->start(); // Start the timer
}

void loop() {
	timer->updateDisplay(); // Update the display with the current elapsed time
}