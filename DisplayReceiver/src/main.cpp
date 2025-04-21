#include <ESPAsyncWebServer.h>

#include <display.h>
#include <timer.h>

Timer* timer = nullptr;


const char* ssid = "StopWatchNetwork"; // Replace with your network SSID
const char* password = "12345678"; // Replace with your network password
const uint16_t serverPort = 8080; // Port for the web server

IPAddress localIP(192, 168, 4, 1); // Local IP address for the access point
IPAddress gateway(192, 168, 4, 1); // Gateway address for the access point
IPAddress subnet(255, 255, 255, 0); // Subnet mask for the access point

AsyncWebServer server(serverPort); // Create a web server on port 80

void notFoundRequest(AsyncWebServerRequest *request) {
	//Handle Unknown Request
	request->send(404);
}

void setup() {
	Serial.begin(115200);
	Serial.println("Starting up...");


	WiFi.mode(WIFI_AP);
	if (!WiFi.config(localIP, gateway, subnet)) {
		Serial.println("STA Failed to configure");
	}
	WiFi.softAP(ssid, password); // Start the access point
	// Configures static IP address

	server.on("/startstop", HTTP_POST, [](AsyncWebServerRequest *request) {
		// Handle start/stop request
		if (timer->start()) {
			request->send(200, "text/plain", "Timer started");
		} else {
			timer->stop(); // Stop the timer if it was already running
			request->send(200, "text/plain", "Timer stopped");
		}
	});
	server.on("/reset", HTTP_POST, [](AsyncWebServerRequest *request) {
		// Handle reset request
		timer->reset(); // Reset the timer
		request->send(200, "text/plain", "Timer reset");
	});
	server.onNotFound(notFoundRequest); // Handle unknown requests
	server.begin(); // Start the server

	initDisplay(100); // Initialize the display

	timer = new Timer(5, 7, display); // Create a timer object with the display
	// timer->start(); // Start the timer
}

void loop() {
	timer->updateDisplay(); // Update the display with the current elapsed time
}