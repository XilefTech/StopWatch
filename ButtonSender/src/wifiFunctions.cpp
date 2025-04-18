#include "wifiFunctions.h"

void reconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
	WiFi.reconnect(); // Attempt to reconnect
	while (WiFi.status() != WL_CONNECTED) {
		delay(100); // Wait for reconnection
	}
}

int initWifi() {
	WiFi.onEvent(reconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

	WiFi.mode(WIFI_STA);
	WiFi.config(config::wifi::local_IP, config::wifi::gateway, config::wifi::subnet);
	WiFi.setHostname(config::wifi::hostname);

	WiFi.begin(config::wifi::ssid, config::wifi::password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}
}

void sendMessage(const char* message) {
	WiFiClient client;
	if (client.connect(config::server::host, config::server::port)) {
		client.println(message); // Send message to server
		client.stop(); // Close the connection
	} else {
		Serial.println("Connection failed!"); // Print error message if connection fails
	}
}