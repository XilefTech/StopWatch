#ifndef ESP_NOW_MESSAGE_H
#define ESP_NOW_MESSAGE_H

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

#endif // ESP_NOW_MESSAGE_H