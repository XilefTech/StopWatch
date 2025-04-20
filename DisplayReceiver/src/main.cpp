#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <digit.h>

#define R1_PIN 13
#define G1_PIN 5 //
#define B1_PIN 17 //
#define R2_PIN 16 //
#define G2_PIN 14
#define B2_PIN 27
#define A_PIN 19 //
#define B_PIN 18 //
#define C_PIN 21 //
#define D_PIN 25
#define E_PIN 12 // not used in 64x32, but I hook it up anyway
#define LAT_PIN 26
#define OE_PIN 32
#define CLK_PIN 33 //

#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define PANEL_CHAIN 1

HUB75_I2S_CFG::i2s_pins _pins = {
	R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN
};
HUB75_I2S_CFG mxconfig(
	PANEL_RES_X, // Module width
	PANEL_RES_Y, // Module height
	PANEL_CHAIN, // chain length
	_pins,
	HUB75_I2S_CFG::FM6126A
);

MatrixPanel_I2S_DMA *display = new MatrixPanel_I2S_DMA(mxconfig);

#define DIGIT_X_OFFSET 5
#define DIGIT_Y_OFFSET 7

Digit *digit1 = new Digit(9, 2, DIGIT_X_OFFSET, DIGIT_Y_OFFSET, display);
Digit *digit2 = new Digit(9, 2, DIGIT_X_OFFSET + 16, DIGIT_Y_OFFSET, display);
Digit *digit3 = new Digit(9, 2, DIGIT_X_OFFSET + 28, DIGIT_Y_OFFSET, display);
Digit *digit4 = new Digit(9, 2, DIGIT_X_OFFSET + 44, DIGIT_Y_OFFSET, display);

void setup() {
	Serial.begin(115200);
	Serial.println("Starting Display Test");

	mxconfig.clkphase = false;
	display->setCfg(mxconfig);
	Serial.println("Configuration set");

	display->begin();
	Serial.println("Display initialized");
	display->setBrightness(255);
	Serial.println("Brightness set to 255");
	display->clearScreen();

	digit1->setValue(0);
	digit2->setValue(0);
	digit3->setValue(0);
	digit4->setValue(0);


	uint16_t separatorColor = display->color565(180, 180, 180);

	// separating colon for minutes and seconds
	display->fillRect(DIGIT_X_OFFSET + 12, DIGIT_Y_OFFSET + 5, 2, 2, separatorColor); 
	display->fillRect(DIGIT_X_OFFSET + 12, DIGIT_Y_OFFSET + 11, 2, 2, separatorColor);

	display->fillRect(DIGIT_X_OFFSET + 40, DIGIT_Y_OFFSET + 16, 2, 2, separatorColor); // decimal dot for seconds
}

void loop() {
	int time = millis();
	digit1->setValue(((time / 10000) / 6) % 10);
	digit2->setValue((time / 10000) % 6);
	digit3->setValue((time / 1000) % 10);
	digit4->setValue((time / 100) % 10);

	// for (int i = 0; i < 10; i++) {
	// 	digit1->setValue(i);
	// 	digit2->setValue(i);
	// 	digit3->setValue(i);
	// 	digit4->setValue(i);
	// 	delay(200);
	// }
}