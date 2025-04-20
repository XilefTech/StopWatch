#ifndef TIMER_H
#define TIMER_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <digit.h>

class Timer {
public:
	Timer(uint16_t xOffset, uint16_t yOffset, MatrixPanel_I2S_DMA *display);

	/**
	 * @brief Start the timer
	 * @return true if the timer was started successfully, false if it was already running
	 */
	bool start();

	/**
	 * @brief Stop the timer
	 * @return The elapsed time in milliseconds since the timer was started if it was running, or the last stopped time if it was not running.
	 * @note If the timer was never started, it will return 0.
	 */
	uint64_t stop();

	/**
	 * @brief Get the elapsed time since the timer was started. If the timer is not running, it will return the last stopped time.
	 * @return The elapsed time in milliseconds
	 * @note If the timer was never started or reset, it will return 0.
	 */
	uint64_t getElapsedTime() const;

	/**
	 * @brief Reset the timer
	 * This will stop the timer and reset the elapsed time to 0.
	 */
	void reset();

	/**
	 * @brief Update the display with the current elapsed time
	 * This will draw the elapsed time on the display.
	 */
	void updateDisplay();

private:
	uint16_t xOffset;
	uint16_t yOffset;
	MatrixPanel_I2S_DMA *display;

	uint64_t startTime;
	uint64_t stopTime;
	bool running;

	// Digits for displaying the time
	Digit *minuteDigit;
	Digit *tenSecondDigit;
	Digit *secondDigit;
	Digit *tenthsDigit;

	void drawSeparators();
};

#endif // TIMER_H
