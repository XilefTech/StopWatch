#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#include <Arduino.h>

struct BatteryLevel {
	String macAddress = "00:00:00:00:00:00"; // MAC address of the device
	String nickName = "";
	int batteryLevel = 0; // Battery level in percentage
};

class BatteryManager {
public:
	BatteryManager();
	// Creates a json string with all battery levels
	String getAllBatteryLevels();
	void setBatteryLevel(String macAddress, int batteryLevel);
	void setNickname(String macAddress, String nickname);
private:
	BatteryLevel batteryLevels[10];
};



#endif // BATTERYMANAGER_H
