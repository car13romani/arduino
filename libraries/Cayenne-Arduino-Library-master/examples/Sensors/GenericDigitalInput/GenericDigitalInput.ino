/*
Cayenne Generic Digital Input Example

This sketch shows how to automatically send data to a Generic Digital Input Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Generic Digital Input widget.
2. Set the widget to 2-State Display.
3. Select a digital pin number. Do not use digital pins 0 or 1 since those conflict with the use of Serial.
4. Attach a digital input device (e.g. a button) to the digital pin on your Arduino matching the selected pin.
5. Set the token variable to match the Arduino token from the Dashboard.
6. Compile and upload this sketch.
7. Once the Arduino connects to the Dashboard it should automatically update the Generic Digital Input widget with data.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneEthernet.h>

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
}

void loop()
{
	Cayenne.run();
}
