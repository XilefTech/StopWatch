# StopWatch
Yet another stopwatch project. This time we use big red buttons and a digital scoreboard


### ButtonSender

One Big red button with a small 1s lipo and an ESP inside, Lipo goes to VIN and through a voltage divider with R1 = (1k+22k+4.7k) = 27.7k, R2 = 100k, _(makes for a ratio of R2 / (R1 + R2) = 0,7892659826, so the 4.2V full charge is approx. 3.3V)_ to Pin 35.

Will Connect to the wifi AP given in its `config.h` and call `POST` Requests for every button press to the given address with the content '`pressed`'. Also battery updates will be sent as soon as they change.


### DisplayReceiver

ESP with HUB75-Matrix attached, displaying the current state of the stopwatch. This unit is also responsible for tracking the time.

Bonus feature: Maybe there will be an interface between a laptop and the esp to transmit battery percentages of the `ButtonSender(s)`


##### Thanks to
https://randomnerdtutorials.com/esp32-client-server-wi-fi/
https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA