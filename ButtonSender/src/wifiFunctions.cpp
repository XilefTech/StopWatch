#include "wifiFunctions.h"

void reconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
	WiFi.reconnect(); // Attempt to reconnect
	while (WiFi.status() != WL_CONNECTED) {
		delay(100); // Wait for reconnection
	}
}

void initWifi() {
	WiFi.onEvent(reconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

	WiFi.mode(WIFI_STA);
	if (config::wifi::useStaticIP) {
		WiFi.config(config::wifi::localIP, config::wifi::gateway, config::wifi::subnet); // Set static IP address
	} else {
		WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); // Use DHCP
	}
	
	WiFi.setHostname(config::wifi::hostname);

	WiFi.begin(config::wifi::ssid, config::wifi::password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}
}

void sendPress() {
	WiFiClient client;
	if (client.connect(config::server::host, config::server::port)) {
		httpPostRequest(client, config::server::endpointAddressStartStop, "pressed"); // Send message to server
		client.stop(); // Close the connection
	} else {
		Serial.println("Connection failed!"); // Print error message if connection fails
	}
}

void sendBatteryUpdate(int batteryLevel) {
	WiFiClient client;
	if (client.connect(config::server::host, config::server::port)) {
		httpPostRequest(client, config::server::endpointAddressBattery, "value=" + String(batteryLevel)); // Send battery status to server
		client.stop(); // Close the connection
	} else {
		Serial.println("Connection failed!"); // Print error message if connection fails
	}
}



int httpPostRequest(WiFiClient& client, const char* serverName, String message) {
	HTTPClient http;
	  
	// Your IP address with path or Domain name with URL path 
	http.begin(client, serverName);

	http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header

	int responseCode = http.POST(message); // Send the request with the message
  
	return responseCode;
}