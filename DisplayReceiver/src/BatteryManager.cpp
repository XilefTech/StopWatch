#include <BatteryManager.h>

BatteryManager::BatteryManager() {
	// Initialize the senders I use, because there is no interface for this yet
	batteryLevels[0].macAddress = "38:18:2B:83:4E:38";
	batteryLevels[0].nickName = "Start Button";

	batteryLevels[1].macAddress = "38:18:2B:83:4E:39";
	batteryLevels[1].nickName = "Stop/Reset Button";
};

String BatteryManager::getAllBatteryLevels() {
	String json = "{[";
	uint8_t addedBatteries = 0;
	for (int i = 0; i < 10; i++) {
		if (batteryLevels[i].macAddress != "00:00:00:00:00:00") {
			if (addedBatteries > 0) {
				json += ",";
			}

			json += "{\"macAddress\":\"" + batteryLevels[i].macAddress + "\",\"nickname\":\"" + batteryLevels[i].nickName + "\",\"batteryLevel\":" + String(batteryLevels[i].batteryLevel) + "}";
			addedBatteries++;
		}
	}
};

void BatteryManager::setBatteryLevel(String macAddress, int batteryLevel) {
	for (int i = 0; i < 10; i++) {
		if (batteryLevels[i].macAddress == macAddress || batteryLevels[i].macAddress == "00:00:00:00:00:00") {
			batteryLevels[i].batteryLevel = batteryLevel;
			return;
		}
	}
};

void BatteryManager::setNickname(String macAddress, String nickname) {
	for (int i = 0; i < 10; i++) {
		if (batteryLevels[i].macAddress == macAddress) {
			batteryLevels[i].nickName = nickname;
			return;
		}
	}
};