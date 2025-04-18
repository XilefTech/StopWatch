#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

// Function to initialize WiFi
// Sets up the WiFi connection and handles reconnections
void initWifi();

// Function to reconnect to WiFi
// This function is called when the WiFi connection is lost
void reconnect(WiFiEvent_t event, WiFiEventInfo_t info);

void sendPress();

void sendBatteryUpdate(int batteryLevel);


// Function to send a post request to the server and return the response
int httpPostRequest(WiFiClient& client, const char* serverName, String message);

#endif // WIFI_H