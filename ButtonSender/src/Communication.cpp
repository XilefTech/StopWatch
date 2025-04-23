#include "Communication.h"

void Communication::reconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
	WiFi.reconnect(); // Attempt to reconnect
	while (WiFi.status() != WL_CONNECTED) {
		delay(100); // Wait for reconnection
	}
}

void Communication::initWifi() {
	hostMac = "";
	WiFi.onEvent(reconnect, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

	WiFi.mode(WIFI_STA);
	if (config::wifi::useStaticIP) {
		WiFi.config(config::wifi::localIP, config::wifi::gateway, config::wifi::subnet); // Set static IP address
	} else {
		WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); // Use DHCP
	}
	WiFi.setHostname(config::wifi::hostname);

	WiFi.begin(config::wifi::ssid, config::wifi::password);
	esp_now_init();

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}

	// Retrieve Host MAC-Address, blink meanwhile to indicate status
	while (hostMac == "") {
		digitalWrite(LED_BUILTIN, LOW);
		hostMac = getHostMacAddress(); // Get the MAC address from the server
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500); // Delay to avoid rapid requests
	}

	espNowHelper.addPeerFromMacAddress(hostMac);
}





void Communication::sendPress() {
	#ifdef useESPNow
		espNowHelper.sendMessage(config::server::messageTypePress, nullptr);
	#else
		doHttpPostRequest(config::server::endpointAddressPress, "pressed");
	#endif
}

void Communication::sendRelease() {
	#ifdef useESPNow
		espNowHelper.sendMessage(config::server::messageTypePress, nullptr);
	#else
		doHttpPostRequest(config::server::endpointAddressRelease, "released");
	#endif
}

void Communication::sendBatteryUpdate(uint8_t batteryLevel) {
	#ifdef useESPNow
		espNowHelper.sendMessage(config::server::messageTypePress, (uint8_t*) &batteryLevel);
	#else
		doHttpPostRequest(config::server::endpointAddressBattery, "value=" + String(batteryLevel));
	#endif
}

String Communication::getHostMacAddress() {
	WiFiClient client;
	if (client.connect(config::server::host, config::server::port)) {
		String macAddress = httpGetRequest(client, config::server::endpointHostMacAddress);
		client.stop(); // Close the connection
		return macAddress;
	} else {
		Serial.println("Connection failed!"); // Print error message if connection fails
		return "";
	}
}



void Communication::doHttpPostRequest(const char* serverName, String message) {
	WiFiClient client;
	if (client.connect(config::server::host, config::server::port)) {
		httpPostRequest(client, serverName, message);
		client.stop(); // Close the connection
	} else {
		Serial.println("Connection failed!");
	}
}


int Communication::httpPostRequest(WiFiClient& client, const char* serverName, String message) {
	HTTPClient http;
	  
	// Your IP address with path or Domain name with URL path 
	http.begin(client, serverName);

	http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Specify content-type header

	int responseCode = http.POST(message); // Send the request with the message
  
	return responseCode;
}

String Communication::httpGetRequest(WiFiClient& client, const char* serverName) {
	HTTPClient http;
	  
	// Your IP address with path or Domain name with URL path 
	http.begin(client, serverName);

	int responseCode = http.GET(); // Send the request with the message
  
	String payload = "";
	if (responseCode>0) {
	    payload = http.getString();
	}
	else {
		Serial.print("Error code: ");
		Serial.println(responseCode);
	}
	// Free resources
	http.end();

	return payload;
}