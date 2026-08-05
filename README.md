# AutoPass-Sensor

  Project’s components: 

o	HW-131 power supply, 

o	Hall current sensor module,

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

  This project's purposes are:

  o	Appropriate barrier movement – the motor starts working only in two cases. First one, if an object was detected by the IR sensor and the barrier position is at 0         degrees or the barrier position is at 90 degrees while the IR sensor is in HIGH state (not detecting anything after the object passed by).

  o	Safe and efficient power system – for the stepper motor to receive power only when needed, it's driver is carefully controlled. This step required a relay, transistor,   1k resistor and one 1n4007 diode.

  o	Current monitoring, event counter and system states:

    1.	The driver's VCC wire is passed through the Hall sensor module's hole to measure current,
   
    2.	As the barrier goes up, the counter will be incremented. If the system is powered after being disconnected for a while a question will pop up on the display,             “Doresti resetarea memoriei? (da/nu)”. If “da” the counter is automatically reset to zero, if “no” counting starts from the previous value it had,
   
    3.	Depending on the current value one led will light up and a message will be displayed on the OLED. When a dangerous value is read, red led lights up, also the             buzzer generates a short sound.

