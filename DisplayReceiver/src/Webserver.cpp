#include <Webserver.h>

Webserver::Webserver() : server(config::serverPort) {
};

void Webserver::startServer() {
	server.on("/start", HTTP_POST, [this](AsyncWebServerRequest *request) {
		if (timer->start()) {
			request->send(200, "text/plain", "Timer started");
		} else {
			request->send(200, "text/plain", "Timer cannot be started at this time");
		}
	});
	server.on("/stop", HTTP_POST, [this](AsyncWebServerRequest *request) {
		timer->stop();
		request->send(200, "text/plain", "Timer stopped");
	});
	server.on("/reset", HTTP_POST, [this](AsyncWebServerRequest *request) {
		timer->reset(); // Reset the timer
		request->send(200, "text/plain", "Timer reset");
	});
	server.on("/macaddress", HTTP_GET, [](AsyncWebServerRequest *request) {
		// Handle MAC address request
		String macAddress = WiFi.macAddress();
		request->send(200, "text/plain", macAddress); // Send the MAC address as a response
	});
	server.onNotFound(notFoundRequest);
	server.begin();
};

void Webserver::notFoundRequest(AsyncWebServerRequest *request) {
	// Handle unknown requests
	request->send(404, "text/plain", "Not Found");
};