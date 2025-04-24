#include <Communication.h>

Timer* Communication::timer = nullptr;

Communication::Communication() : webserver() {
	
};

void Communication::initialize() {
	WiFi.mode(WIFI_AP);
	if (!WiFi.config(config::localIP, config::gateway, config::subnet)) {
		Serial.println("STA Failed to configure");
	}
	WiFi.softAP(config::ssid, config::password); // Start the access point

	webserver.startServer();

	// Init ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}
	esp_now_register_recv_cb(esp_now_recv_cb_t(onReceiveCallBack));
};


void Communication::setTimer(Timer* timer) {
	this->timer = timer;
	webserver.setTimer(timer);
};

void Communication::onReceiveCallBack(const uint8_t* macAddress, const uint8_t* data, int length) {
	Serial.printf("Received data from: %02X:%02X:%02X:%02X:%02X:%02X\n",
		macAddress[0], macAddress[1], macAddress[2], macAddress[3], macAddress[4], macAddress[5]);

	ESPNOWMessage message;
	memcpy(&message, data, sizeof(message)); // Copy the received data into the message struct
	Serial.printf("Decoded data: Message type: %d, data: %d\n", message.type, message.data);
	if (message.type == ESPNOWMessageType::NONE) {
		return;
	}

	if (message.type == ESPNOWMessageType::START) {
		timer->start();
	} else if (message.type == ESPNOWMessageType::STOP) {
		timer->stop();
	} else if (message.type == ESPNOWMessageType::RESET) {
		timer->reset();
	} else if (message.type == ESPNOWMessageType::BATTERY) {
		// TODO
	}
};