#include <Webserver.h>

Webserver::Webserver() : server(config::serverPort) {
	batteryManager = new BatteryManager();
};

void Webserver::startServer() {
	Serial.println("Starting LittleFS...");
	if(!LittleFS.begin()){
		Serial.println("An Error has occurred while mounting LittleFS");
		return;
	}
	Serial.println("LittleFS mounted successfully.");

	Serial.println("Starting web server...");
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
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
		// The main page
		request->send(LittleFS, "/index.html"); // Send the MAC address as a response
	});
	server.on("/battery-status", HTTP_GET, [this](AsyncWebServerRequest *request) {
		// The main page
		request->send(200, "text/json", batteryManager->getAllBatteryLevels()); // Send the MAC address as a response
	});
	server.onNotFound(notFoundRequest);
	server.begin();

	Serial.println("Web server started.");

	Serial.print("Station MAC address: ");
	Serial.println(WiFi.softAPmacAddress()); // Print the MAC address of the access point

	Serial.print("ESPWifi MAC address: ");
	uint8_t baseMac[6];
	  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
	  if (ret == ESP_OK) {
	    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
	                  baseMac[0], baseMac[1], baseMac[2],
	                  baseMac[3], baseMac[4], baseMac[5]);
	  } else {
	    Serial.println("Failed to read MAC address");
	  }
};

void Webserver::notFoundRequest(AsyncWebServerRequest *request) {
	// Handle unknown requests
	request->send(404, "text/plain", "Not Found");
};