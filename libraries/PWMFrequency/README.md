PWM Frequency Arduino Library
=============================

Library for Setting the PWM Frequency

Please keep in mind that changing the PWM frequency changes the Atmega's timers and disrupts the normal operation of many functions that rely on time (delay(), millis(), Servo library).

This Library support both ATMega 328 and 32U4 (Leonardo)

Example
=======

Here are some usage examples of the function:

// Set pin 9's PWM frequency to 3906 Hz (31250/8 = 3906)
// Note that the base frequency for pins 3, 9, 10, and 11 is 31250 Hz
setPwmFrequency(9, 8);

// Set pin 6's PWM frequency to 62500 Hz (62500/1 = 62500)
// Note that the base frequency for pins 5 and 6 is 62500 Hz
setPwmFrequency(6, 1);

// Set pin 10's PWM frequency to 31 Hz (31250/1024 = 31)
setPwmFrequency(10, 1024);

See
===

http://playground.arduino.cc/Code/PwmFrequency

Thanks to macegr of the Arduino forums for his documentation of the PWM frequency divisors. His post can be viewed at:
http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1235060559/0#4

Thanks to mactester57 for providing ATMega 32U4 testing
http://www.tonymacx86.com/imac-mods/107859-kiwis-next-project-imac-g5-10.html#post765116
 
Version History
===============

2.0 2014-07-30 Added Support for ATMega 32U4 Leonardo timers



