#include <Arduino.h>
#include <WiFi.h>
#include "config.h"


int initWifi();


void setup() {
	initWifi();
}

void loop() {
	while (WiFi.status() == WL_CONNECTED) {
		delay(1000); // Placeholder for actual work
	}
	WiFi.reconnect(); // Attempt to reconnect if disconnected
	while (WiFi.status() != WL_CONNECTED) {
		delay(100); // Wait for reconnection
	}
}



int initWifi() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(config::wifi::networkName, config::wifi::password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
	}

	WiFi.config(config::wifi::local_IP, config::wifi::gateway, config::wifi::subnet);
}