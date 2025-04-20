#ifndef DIGIT_H
#define DIGIT_H

#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Digit {
public:
	// Constructor
	Digit(byte value, byte size, uint16_t posX, uint16_t posY, MatrixPanel_I2S_DMA *display);

	// Set value of the digit and update the display
	void setValue(byte value);

private:
	// Display object
	MatrixPanel_I2S_DMA *display;

	// Position of the digit on the display
	uint16_t posX;
	uint16_t posY;

	// Size of the digit
	byte size;

	// Current value of the digit
	byte currentValue;

	// Draw the digit on the display
	void updateDisplay();

	// Draw a single segment of the digit
	void drawSegment(uint8_t segment, bool on);
};

#endif // DIGIT_H
