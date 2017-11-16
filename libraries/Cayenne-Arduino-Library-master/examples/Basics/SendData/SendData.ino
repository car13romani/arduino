/*
Cayenne SendData Example

This example sketch shows how a value can be sent from Arduino to the Cayenne Dashboard on a Virtual Pin.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Create a Generic Analog Input widget attached to Virtual Pin 5 in the Cayenne Dashboard.
2. Set the token variable to match the Arduino token from the Dashboard.
3. Compile and upload the sketch.

NOTE:
 For this example you'll need SimpleTimer library:
   https://github.com/jfturcot/SimpleTimer
 Visit this page for more information:
   http://playground.arduino.cc/Code/SimpleTimer
*/

#define CAYENNE_PRINT Serial    // Comment this out to disable prints and save space
#include <CayenneEthernet.h>    // Change this to use a different communication device. See Communications examples.
#include <SimpleTimer.h>

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin 5.
void sendUptime()
{
	// Send values using the virtualWrite function. Cayenne currently accepts int and float values.
	// Please don't send more that 10 values per second.
	Cayenne.virtualWrite(V5, millis() / 1000);
}

void setup()
{
	Serial.begin(9600); // See the connection status in Serial Monitor
	Cayenne.begin(token);

	// Setup a function to be called every second
	timer.setInterval(1000L, sendUptime);
}

void loop()
{
	Cayenne.run(); // Runs main loop
	timer.run(); // Initiates SimpleTimer
}

