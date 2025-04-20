#include <digit.h>

/*
We use a 7-segment display with the following pinout:
	---A---
	|     |
	F     B
	|     |
	---G---
	|     |
	E     C
	|     |
	---D---
*/
uint8_t digitBits[] = {
	B01111110, // 0 ABCDEF-
	B00110000, // 1 -BC----
	B01101101, // 2 AB-DE-G
	B01111001, // 3 ABCD--G
	B00110011, // 4 -BC--FG
	B01011011, // 5 A-CD-FG
	B01011111, // 6 A-CDEFG
	B01110000, // 7 ABC----
	B01111111, // 8 ABCDEFG
	B01111011, // 9 ABCD_FG
};


Digit::Digit(byte value, byte size, uint16_t posX, uint16_t posY, MatrixPanel_I2S_DMA *display) {
	this->display = display;
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	this->currentValue = value;
	updateDisplay();
};


void Digit::setValue(byte value) {
	if (value != currentValue) {
		currentValue = value;
		updateDisplay();
	}
};

void Digit::updateDisplay() {
	display->fillRect(posX, posY, size * 5, size * 10, display->color565(0, 0, 0)); // Clear the digit area

	uint8_t firstSegmentIndex = 0x40;
	
	for (int i = 0; i < 8; i++) {
		if (digitBits[currentValue] & (firstSegmentIndex >> i)) {
			drawSegment(i, true); // Draw the segment in white (on)
		}
	}
};

void Digit::drawSegment(uint8_t segment, bool on) {
	u_int16_t color = on ? display->color565(255, 255, 255) : display->color565(0, 0, 0);

	switch (segment) {
		case 0: // A
			display->fillRect(posX, posY, size * 5, size, color);
			break;
		case 1: // B
			display->fillRect(posX + size * 4, posY, size, size * 5, color);
			break;
		case 2: // C
			display->fillRect(posX + size * 4, posY + size * 4, size, size * 5, color);
			break;
		case 3: // D
			display->fillRect(posX, posY + size * 8, size * 5, size, color);
			break;
		case 4: // E
			display->fillRect(posX, posY + size * 4, size, size * 5, color);
			break;
		case 5: // F
			display->fillRect(posX, posY, size, size * 5, color);
			break;
		case 6: // G
			display->fillRect(posX, posY + size * 4, size * 5, size, color);
			break;
		default:
			break;
	}
};


