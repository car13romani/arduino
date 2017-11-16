/*
Cayenne SyncData Example

This example sketch shows how a value in the Cayenne Dashboard can be synced with the Arduino on a Virtual Pin.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Create a Generic Digital Output Actuator widget attached to Virtual Pin 6 in the Cayenne Dashboard.
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

void setup()
{
	Serial.begin(9600); // See the connection status in Serial Monitor
	Cayenne.begin(token);

	// Setup a function to be called every 5 seconds
	timer.setInterval(5000L, syncData);
}

void loop()
{
	Cayenne.run(); // Runs main loop
	timer.run(); // Initiates SimpleTimer
}

// This function syncs the Virtual Pin 6 data.
void syncData()
{
	CAYENNE_LOG("Sync data");
	// Sync the Virtual Pin. This sends a request to the server to resend data for the pin.
	// This will cause the CAYENNE_IN function to be called.
	Cayenne.syncVirtual(V6);
}

CAYENNE_IN(V6)
{
	CAYENNE_LOG("Current value: %s", getValue.asStr());
}
