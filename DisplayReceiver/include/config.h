#ifndef CONFIG_H
#define CONFIG_H

#define USE_ESP_NOW // comment this line to use HTTP instead of ESP-NOW

namespace config {
	inline const char* ssid = "StopWatchNetwork"; // Replace with your network SSID
	inline const char* password = "12345678"; // Replace with your network password
	constexpr uint16_t serverPort = 8080; // Port for the web server

	inline IPAddress localIP(192, 168, 4, 1); // Local IP address for the access point
	inline IPAddress gateway(192, 168, 4, 1); // Gateway address for the access point
	inline IPAddress subnet(255, 255, 255, 0); // Subnet mask for the access point
};


#endif // CONFIG_H
