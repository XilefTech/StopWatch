#ifndef WEBSERVER_HH
#define WEBSERVER_HH

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <config.h>
#include <timer.h>

/**
 * @brief Webserver class to handle HTTP requests and responses.
 * This class uses the ESPAsyncWebServer library to create a web server on the ESP32.
 */
class Webserver {
public:
	Webserver();
	void startServer(); // Start the web server
	inline void setTimer(Timer* timer) { this->timer = timer; };
private:
	AsyncWebServer server; // Create a web server on port 80
	Timer* timer;
	static void notFoundRequest(AsyncWebServerRequest *request); // Handle unknown requests
};


#endif // WEBSERVER_HH
