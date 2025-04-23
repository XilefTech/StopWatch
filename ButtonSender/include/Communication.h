#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "ESPNowHelper.h"


class Communication {
public:
	// Function to initialize WiFi
	// Sets up the WiFi connection and handles reconnections
	void initWifi();

	void sendPress();

	void sendRelease();

	void sendBatteryUpdate(uint8_t batteryLevel);

	String getHostMacAddress();


private:
	// Mac-Address of host device for ESP-NOW communication
	String hostMac;

	ESPNowHelper espNowHelper;

	// Function to reconnect to WiFi
	// This function is called when the WiFi connection is lost
	static void reconnect(WiFiEvent_t event, WiFiEventInfo_t info);

	int httpPostRequest(WiFiClient& client, const char* serverName, String message);

	String httpGetRequest(WiFiClient& client, const char* serverName);

	void doHttpPostRequest(const char* serverName, String message);
};

#endif // WIFI_H