#ifndef ESPNOWHELPER_H
#define ESPNOWHELPER_H

#include <Arduino.h>
#include <esp_now.h>

class ESPNowHelper {
public:
	void addPeerFromMacAddress(const String& macAddress);

	/**
	 * @brief Send a message using ESP-NOW to the peer device, previously added with addPeerFromMacAddress.
	 * @param messageType The type of message to send.
	 * @param data Pointer to the data to send. For most message types, no data is needed, so this can be nullptr.
	 * @return ESP_OK on success, or an error code on failure.
	 */
	esp_err_t sendMessage(ESPNOWMessageType messageType, uint8_t* data);

private:
	esp_now_peer_info_t peerInfo;

	void createPeerInfo(const String& hostMac);
};

enum class ESPNOWMessageType : uint8_t {
	START = 0x00,
	STOP = 0x01,
	RESET = 0x02,
	BATTERY = 0x03,
	NONE = 0xFF // No message type, used for no data
};

struct ESPNOWMessage {
	ESPNOWMessageType type;
	uint8_t data; // Adjust size as needed
};

#endif // ESPNOWHELPER_H
