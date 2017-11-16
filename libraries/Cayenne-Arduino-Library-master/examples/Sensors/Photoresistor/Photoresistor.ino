/*
Cayenne Photoresistor Example

This sketch shows how to automatically send data to a Photoresistor Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Photoresistor widget.
2. Set the widget to Value Display.
3. Select the Integrated ADC and a pin number.
4. Attach a photoresistor to the analog pin on your Arduino matching the selected pin.
   Make sure to use an analog pin, not a digital pin.
   Schematic:
   [Ground] -- [10k-resistor] -- | -- [Photoresistor] -- [5V]
                                 |
                            Analog Pin
5. Set the token variable to match the Arduino token from the Dashboard.
6. Compile and upload this sketch.
7. Once the Arduino connects to the Dashboard it should automatically update the Photoresistor widget with data.
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
