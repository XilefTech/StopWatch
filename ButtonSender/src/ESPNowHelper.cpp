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
		return ESP_OK; // Invalid argument if no message type is provided
	}

	// Create the message struct
	ESPNOWMessage message;
	message.type = messageType;
	if (data != nullptr)  {
		message.data = *data;
	}

	// Send the message using ESP-NOW
	return esp_now_send(peerInfo.peer_addr, (uint8_t*) &message, sizeof(message));
}

// see https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
void ESPNowHelper::createPeerInfo(const String& hostMac) {
	uint8_t macAddress[6];
	for (int i = 0; i < 6; i++) {
		// mac address is xx:xx:xx:xx:xx, we want to avoid all colons, so we go in steps of 3 characters
		macAddress[i] = hostMac.substring(3 * i, 3 * i + 2).toInt();
	}

	memcpy(peerInfo.peer_addr, macAddress, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;
}