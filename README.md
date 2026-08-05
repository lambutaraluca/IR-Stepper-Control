# AutoPass-Sensor


### __The IR-Stepper-Control project is designed to operate safely and efficiently.__
### __It can be integrated into a smart parking system, industrial belt conveyors or automated people counter for retail stores.__

#### __This project's purposes are:__

  	o	Appropriate barrier movement – the motor starts working only in two cases: 
	
		1.	an object was detected by the IR sensor and the barrier position is at 0 degrees, 
		
		2.	the barrier position is at 90 degrees while the IR sensor is in HIGH state (not detecting anything after the object passed by).


 	o	Safe and efficient power system – for the stepper motor to receive power only when needed, it's driver is carefully controlled. This step required a relay, transistor, 1k resistor and one 1n4007 diode.
  
		1.	The transistor is used as a switch, along with the resistor, which is used for safety reasons like limiting the current, is connected to an Arduino digital pin. Using an NPN transistor the logic is LOW-Side-Switching.
	
		2.	As the pin is in HIGH state(the IR sensor pin also) the current flows to the relay coil, triggering the relay to switch to NO(Normally Open).

		3.	The driver is supplied with power and the stepper motor turns. 

  
  	o	Current monitoring, event counter and system states:

		1.	The driver's VCC wire is passed through the Hall sensor module's hole to measure current,
   
		2.	As the barrier goes up, the counter will be incremented. If the system is powered after being disconnected for a while a question will pop up on the display, “Doresti resetarea memoriei? (da/nu)”. If “da” the counter is automatically reset to zero, using the EEPROM memory, if “no” counting starts from the previous value it had,
   
		3.	Depending on the current value one led will light up and a message will be displayed on the OLED. When a dangerous value is read, red led lights up, also the buzzer generates a short sound.



#### __Project’s components:__

  	o	HW-131 power supply, 

  	o	WCS1800 Hall current sensor module,

  	o	28BYJ-48 stepper motor,

  	o	ULN2003 driver,

  	o	SRD-05VDC-SL-C relay,

  	o	IR infrared obstacle avoidance sensor module,

  	o	OLED display,

  	o	Active buzzer,

  	o	BD139 NPN transistor,

  	o	1k ohm resistor,

  	o	1n4007 diode,

  	o	3 x 202 ohms resistor.
