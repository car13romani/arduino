/*
Cayenne SyncAll Example

This example sketch shows how the widgets in the Cayenne Dashboard can be synced with the Arduino when a
successful connection occurs.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Create a Generic Digital or Analog Output Actuator widget attached to Virtual Pin 6 in the Cayenne Dashboard.
2. Create a Generic Digital or Analog Output Actuator widget attached to Virtual Pin 7 in the Cayenne Dashboard.
3. Set the token variable to match the Arduino token from the Dashboard.
4. Compile and upload the sketch.
*/

#define CAYENNE_PRINT Serial    // Comment this out to disable prints and save space
#include <CayenneEthernet.h>    // Change this to use a different communication device. See Communications examples.

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

// This flag is used so the sync only happens on the first connection.
bool isFirstConnect = true;

void setup()
{
	Serial.begin(9600); // See the connection status in Serial Monitor
	Cayenne.begin(token);
}

void loop()
{
	Cayenne.run(); // Runs main loop
}

// This function will run every time the Cayenne connection is established.
CAYENNE_CONNECTED()
{
	CAYENNE_LOG("Connection established");
	if (isFirstConnect)
	{
		// This causes Cayenne to resend data for any virtual pins.
		Cayenne.syncAll();
		isFirstConnect = false;
	}
}

CAYENNE_IN(V6)
{
	CAYENNE_LOG("Current Virtual Pin 6 value: %s", getValue.asStr());
}

CAYENNE_IN(V7)
{
	CAYENNE_LOG("Current Virtual Pin 7 value: %s", getValue.asStr());
}
