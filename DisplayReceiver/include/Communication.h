#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Webserver.h>
#include <esp_now.h>
#include <ESPNowMessage.h>

class Communication {
public:
	Communication();

	void initialize();

	void setTimer(Timer* timer);

private:
	static Webserver webserver;
	static Timer* timer;

	static void onReceiveCallBack(const uint8_t* macAddress, const uint8_t* data, int length);
};



#endif // COMMUNICATION_H
