/*
Cayenne SendDataOnRequest Example

This example sketch shows how a value can be sent from Arduino to the Cayenne Dashboard in 
response to a Virtual Pin request.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Create a Generic Analog Input widget attached to Virtual Pin 5 in the Cayenne Dashboard.
2. Set the token variable to match the Arduino token from the Dashboard.
3. Compile and upload the sketch.
*/

#define CAYENNE_PRINT Serial
#include <CayenneEthernet.h>   // Change this to use a different communication device. See Communications examples.

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

// Use Virtual Pin 5 for uptime display.
#define VIRTUAL_PIN V5

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
}

void loop()
{
	Cayenne.run();
}

// This function is called when a Cayenne widget requests data for Virtual Pin 5.
CAYENNE_OUT(VIRTUAL_PIN)
{
	CAYENNE_LOG("Data requested for Virtual Pin %d", VIRTUAL_PIN);
	// This command writes Arduino's uptime in seconds to the Virtual Pin.
	Cayenne.virtualWrite(VIRTUAL_PIN, millis() / 1000);
}
