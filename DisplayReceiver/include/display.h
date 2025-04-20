#ifndef DISPLAY_H
#define DISPLAY_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#define R1_PIN 13
#define G1_PIN 5
#define B1_PIN 17
#define R2_PIN 16
#define G2_PIN 14
#define B2_PIN 27
#define A_PIN 19
#define B_PIN 18
#define C_PIN 21
#define D_PIN 25
#define E_PIN -1 // not used in 64x32
#define LAT_PIN 26
#define OE_PIN 32
#define CLK_PIN 33

#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define PANEL_CHAIN 1

inline HUB75_I2S_CFG::i2s_pins _pins = {
	R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN
};
inline HUB75_I2S_CFG mxconfig(
	PANEL_RES_X, // Module width
	PANEL_RES_Y, // Module height
	PANEL_CHAIN, // chain length
	_pins,
	HUB75_I2S_CFG::FM6126A
);

inline MatrixPanel_I2S_DMA *display = new MatrixPanel_I2S_DMA(mxconfig);

void initDisplay(uint8_t brightness);

#endif // DISPLAY_H
