#include <timer.h>



Timer::Timer(uint16_t xOffset, uint16_t yOffset, MatrixPanel_I2S_DMA *display) {
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->display = display;

	startTime = 0;
	stopTime = 0;
	running = false;
	resetted = true;

	minuteDigit 	= new Digit(0, 2, xOffset, yOffset, display);
	tenSecondDigit 	= new Digit(0, 2, xOffset + 16, yOffset, display);
	secondDigit 	= new Digit(0, 2, xOffset + 28, yOffset, display);
	tenthsDigit 	= new Digit(0, 2, xOffset + 44, yOffset, display);

	drawSeparators();
}

bool Timer::start() {
	if (!resetted) {
		return false;
	}
	if (!running) {
		startTime = millis();
		running = true;
		resetted = false;
		return true;
	}
	return false;
}

uint64_t Timer::stop() {
	if (running) {
		stopTime = millis();
		running = false;
		updateDisplay();
		return stopTime - startTime;
	}
	return stopTime - startTime;
}

uint64_t Timer::getElapsedTime() const {
	if (running) {
		return millis() - startTime;
	}
	return stopTime - startTime;
}

void Timer::reset() {
	startTime = 0;
	stopTime = 0;
	running = false;
	resetted = true;
	updateDisplay();
}

void Timer::updateDisplay() {
	uint64_t elapsedTime = getElapsedTime();
	uint8_t minutes 	= ((elapsedTime / 10000) / 6) % 10;
	uint8_t tenSeconds 	= (elapsedTime / 10000) % 6;
	uint8_t seconds		= (elapsedTime / 1000) % 10;
	uint8_t tenths		= (elapsedTime / 100) % 10;

	
	minuteDigit->setValue(minutes);
	tenSecondDigit->setValue(tenSeconds);
	secondDigit->setValue(seconds);
	tenthsDigit->setValue(tenths);
}

void Timer::drawSeparators() {
	uint16_t separatorColor = display->color565(180, 180, 180);

	// separating colon for minutes and seconds
	display->fillRect(xOffset + 12, yOffset + 5, 2, 2, separatorColor); 
	display->fillRect(xOffset + 12, yOffset + 11, 2, 2, separatorColor);

	display->fillRect(xOffset + 40, yOffset + 16, 2, 2, separatorColor); // decimal dot for seconds
}