#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>
#include "config.h"


// returns the battery voltage in millivolts (0-1000 mV)
int getBatteryVoltage() {
	// read from ADC pin
	int batteryVoltage = analogReadMilliVolts(config::battery::pin);
	return batteryVoltage * config::battery::voltageFactor;
}

// Returns the battery level as a percentage (0-100%)
int getBatteryPercent() {
	// battery value as a number between 0 and 1
	float batteryValue = (getBatteryVoltage() - config::battery::minVoltage) / (config::battery::maxVoltage - config::battery::minVoltage);
	return batteryValue * 100;
}

#endif // BATTERY_H
