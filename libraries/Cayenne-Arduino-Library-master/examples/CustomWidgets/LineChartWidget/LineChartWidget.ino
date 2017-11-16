/*
Cayenne Line Chart Widget Example

This sketch shows how to set up a Line Chart Widget with Cayenne.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Line Chart Custom Widget.
3. Select Virtual I/O and a virtual pin number.
4. Set VIRTUAL_PIN to the pin number you selected.
5. Select a data type and unit, e.g. Temperature, Celsius.
6. Attach an analog input device (e.g. a temperature sensor) to your Arduino.
7. Set the token variable to match the Arduino token from the Dashboard.
8. Modify the CAYENNE_OUT(VIRTUAL_PIN) function to send data from your sensor.
9. Compile and upload this sketch.
10. Once the Arduino connects to the Dashboard it should automatically update the Line Chart widget with data.

For further examples of how to send data to Cayenne see the example sketches under Sensors.
*/

#define CAYENNE_PRINT Serial   // Comment this out to disable prints and save space
#include <CayenneEthernet.h>   // Change this to use a different communication device. See Communications examples.

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

// Virtual Pin of the widget.
#define VIRTUAL_PIN V1

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
}

void loop()
{
	Cayenne.run();
}

// This function is called when the Cayenne widget requests data for the Virtual Pin.
CAYENNE_OUT(VIRTUAL_PIN)
{
	// Read data from the sensor and send it to the virtual channel here.
	// You can write data using virtualWrite or other Cayenne write functions.
	// For example, to send a temperature in Celsius you can use the following:
	// Cayenne.virtualWrite(VIRTUAL_PIN, 25.5, TEMPERATURE, CELSIUS);
}