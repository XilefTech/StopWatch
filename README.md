# StopWatch
Yet another stopwatch project. This time we use big red buttons and a digital scoreboard


### ButtonSender

One Big red button with a small 1s lipo and an ESP inside, Lipo goes to VIN and through a voltage divider with R1 = (1k+22k+4.7k) = 27.7k, R2 = 100k, _(makes for a ratio of R2 / (R1 + R2) = 0,7892659826, so the 4.2V full charge is approx. 3.3V)_ to Pin 4.

Will Connect to the wifi AP given in its `config.h` and call `POST` Requests for every button press to the given address with the content '`pressed`'. Also battery updates will be sent as soon as they change.