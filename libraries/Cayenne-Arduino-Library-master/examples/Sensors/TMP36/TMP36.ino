/*
Cayenne TMP36 Example

This sketch shows how to send temperature data to a TMP36 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new TMP36 widget.
2. Set the widget to Value Display.
3. Select Virtual Pins and a virtual pin number.
4. Set VIRTUAL_PIN to the pin number you selected.
5. Attach a TMP36 to an analog pin on your Arduino. Make sure to use an analog pin, not a digital pin.
   Schematic:
   [Ground] -- [TMP36] -- [5V]
                  |
              Analog Pin
6. Set the tmpPin variable to match the pin used to connect the TMP36.
7. Set the voltage variable to match the voltage used to connect the TMP36.
8. Set the token variable to match the Arduino token from the Dashboard.
9. Compile and upload this sketch.
10. Once the Arduino connects to the Dashboard it should automatically update the TMP36 widget with data.
*/

#define CAYENNE_PRINT Serial   // Comment this out to disable prints and save space
#include <CayenneTemperature.h>
#include <CayenneEthernet.h>   // Change this to use a different communication device. See Communications examples.

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

// Virtual Pin of the TMP36 widget.
#define VIRTUAL_PIN V1

// Analog pin the TMP36 is connected to.
const int tmpPin = 0;

// Voltage to the TMP36. For 3v3 Arduinos use 3.3.
const float voltage = 5.0; 

TMP36 tmpSensor(tmpPin, voltage);

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
	// This command writes the temperature in Celsius to the Virtual Pin.
	Cayenne.celsiusWrite(VIRTUAL_PIN, tmpSensor.getCelsius());
	// To send the temperature in Fahrenheit or Kelvin use the corresponding code below.
	//Cayenne.fahrenheitWrite(VIRTUAL_PIN, tmpSensor.getFahrenheit());
	//Cayenne.kelvinWrite(VIRTUAL_PIN, tmpSensor.getKelvin());
}
