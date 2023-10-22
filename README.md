# STOP_WATCH_ATMEGA32

a Stop Watch system using an ATmega32 microcontroller, six Common Anode 7-segment displays with a 7447 decoder and three push buttons.
Here are some key features:

- Timer1 in CTC mode: Timer1 to accurately count time intervals.

- Multiplexed 7-segments: The six 7-segment displays are multiplexed to display time.

- Three push buttons: used to control the stopwatch.


 This project is implemented using External Interrupts: 

1️- INT0 : Reset the stopwatch time with a falling edge, using a push button with an internal pull-up resistor.

2️- INT1 : Pause the stopwatch time with a rising edge, using a push button with an external pull-down resistor.

3️- INT2 : Resume the stopwatch time with a falling edge, using a push button with an internal pull-up resistor.
