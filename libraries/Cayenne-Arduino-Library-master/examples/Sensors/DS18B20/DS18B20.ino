/*
Cayenne DS18B20 Example

This sketch shows how to send temperature data to a DS18B20 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Install the OneWire library (http://www.pjrc.com/teensy/td_libs_OneWire.html) from the Arduino Library Manager.
2. Install the DallasTemperature library (http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library#Code.2FLibrary) from the Arduino Library Manager.
3. In the Cayenne Dashboard add a new DS18B20 widget.
4. Set the widget to Value Display.
5. Select Virtual Pins and a virtual pin number.
6. Set VIRTUAL_PIN to the pin number you selected.
7. Attach a DS18B20 to an digital pin on your Arduino.
   Schematic:
   [Ground] -- [DS18B20] -- [4.7k resistor] -- [5V]
                   |______________|
                   |
              Digital Pin
8. Set the tmpPin variable to match the pin used to connect the DS18B20.
9. Set the token variable to match the Arduino token from the Dashboard.
10. Compile and upload this sketch.
11. Once the Arduino connects to the Dashboard it should automatically update the DS18B20 widget with data.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <OneWire.h>
#include <DallasTemperature.h>
#include <CayenneEthernet.h>

// Virtual Pin of the DS18B20 widget.
#define VIRTUAL_PIN V1

// Digital pin the DS18B20 is connected to. Do not use digital pins 0 or 1 since those conflict with the use of Serial.
const int tmpPin = 2;

OneWire oneWire(tmpPin);
DallasTemperature sensors(&oneWire);

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
	sensors.begin();
}

void loop()
{
	Cayenne.run();
}

// This function is called when the Cayenne widget requests data for the Virtual Pin.
CAYENNE_OUT(VIRTUAL_PIN)
{
	// Send the command to get temperatures.
	sensors.requestTemperatures();
	// This command writes the temperature in Celsius to the Virtual Pin.
	Cayenne.celsiusWrite(VIRTUAL_PIN, sensors.getTempCByIndex(0));
	// To send the temperature in Fahrenheit use the corresponding code below.
	//Cayenne.fahrenheitWrite(VIRTUAL_PIN, sensors.getTempFByIndex(0));
}
