# AutoPass-Sensor

Project components: 
o	HW-131 power supply, 
o	Hall current sensor module
o	Stepper motor,
o	ULN2003 driver,
o	5V relay,
o	IR sensor,
o	OLED display,
o	Active buzzer,
o	BD139 NPN transistor,
o	1k ohm resistor,
o	1n4007 diode,
o	3 x 202 ohms resistor.

This project’s purposes are:
o	Barrier movement accordingly – the motor starts working only in two cases. First one, if an object was detected by the IR sensor and the barrier position is at 0 degrees or the barrier position is at 90 degrees while the IR sensor is in HIGH state(not detecting anyting after the object passed by).
o	Safe and efficient power system – for the stepper motor to be receive power only when needed it’s the driver is controlled carefully. This step required a relay, transistor, 1k resistor and one 1n4007 diode.
o	Current control measure – the Hall current sensor module has the VCC driver’s wire wrapped up the through-hole. Depending on the current value one led will light up, if a dangerous measure is read in that case along the red led also a buzzer generate a short sound.

