#include <display.h>
#include <timer.h>
#include <Communication.h>
#include <Ascii-print.h>

Timer* timer = nullptr;

Communication communication;


void setup() {
	Serial.begin(115200);
	Serial.println("Welcome to \n");
	Serial.println(ascii_print::stopWatch);
	Serial.println("DisplayReceiver - ESP32\n");
	Serial.println("Starting up...");

	communication.initialize();
	

	initDisplay(100); // Initialize the display

	timer = new Timer(5, 7, display); // Create a timer object with the display

	communication.setTimer(timer);
}

void loop() {
	timer->updateDisplay(); // Update the display with the current elapsed time
}