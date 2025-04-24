#include <ESPNowHelper.h>

void ESPNowHelper::addPeerFromMacAddress(const String& macAddress) {
	createPeerInfo(macAddress);

	auto status = esp_now_add_peer(&peerInfo);
	while (status != ESP_OK && status != ESP_ERR_ESPNOW_EXIST) {
		status = esp_now_add_peer(&peerInfo);
	}
}

esp_err_t ESPNowHelper::sendMessage(ESPNOWMessageType messageType, uint8_t* data) {
	if (messageType == ESPNOWMessageType::NONE) {
		Serial.println("[ESP-NOW-Helper] Empty message, discarding.");
		return ESP_OK; // Invalid argument if no message type is provided
	}
	Serial.println("[ESP-NOW-Helper] Sending message: " + String((uint8_t) messageType));

	// Create the message struct
	ESPNOWMessage message;
	message.type = messageType;
	if (data != nullptr)  {
		message.data = *data;
	}

	// Send the message using ESP-NOW
	esp_err_t status = esp_now_send(peerInfo.peer_addr, (uint8_t*) &message, sizeof(message));
	if (status == ESP_OK) {
		Serial.println("[ESP-NOW-Helper] Message sent successfully.");
	} else {
		Serial.println("[ESP-NOW-Helper] Error sending message: " + String(status));
	}
	return status;
}

// see https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
void ESPNowHelper::createPeerInfo(const String& hostMac) {
	Serial.println("[ESP-NOW-Helper] Creating peer info from MAC address: " + hostMac);

	uint8_t macAddress[6];
	for (int i = 0; i < 6; i++) {
		// mac address is xx:xx:xx:xx:xx, we want to avoid all colons, so we go in steps of 3 characters
		String substring = hostMac.substring(3 * i, 3 * i + 2);
		macAddress[i] = strtol(substring.c_str(), nullptr, 16);
		Serial.printf("[ESP-NOW-Helper] Parsed byte %d: '%s' into '%02X'\n", i, substring, macAddress[i]);
	}

	Serial.printf("[ESP-NOW-Helper] Creating peer info with parsed MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
		macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);
	memcpy(peerInfo.peer_addr, macAddress, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;
}