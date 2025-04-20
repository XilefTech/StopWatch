#include <display.h>

void initDisplay(uint8_t brightness = 255) {
	mxconfig.clkphase = false;
	display->setCfg(mxconfig);
	display->begin();

	display->setBrightness(brightness);
	display->clearScreen();
}