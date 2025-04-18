#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

// Function to initialize WiFi
// Sets up the WiFi connection and handles reconnections
int initWifi();

// Function to reconnect to WiFi
// This function is called when the WiFi connection is lost
void reconnect(WiFiEvent_t event, WiFiEventInfo_t info);

void sendMessage(const char* message);

#endif // WIFI_H