/*
Cayenne TSL2561 Example

This sketch shows how to send luminosity data to a TSL2561 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Install the Adafruit Unified Sensor library (https://github.com/adafruit/Adafruit_Sensor) from the Arduino Library Manager.
2. Install the Adafruit TSL2561 library (https://github.com/adafruit/Adafruit_TSL2561) from the Arduino Library Manager.
3. In the Cayenne Dashboard add a new TSL2561 widget.
4. Set the widget to Value Display.
5. Select Virtual Pins and a virtual pin number.
6. Set VIRTUAL_PIN to the pin number you selected.
7. Attach a TSL2561 to your Arduino.
   Schematic:
   TSL2561   Arduino
   [VCC] --- [3V3]
   [GND] --- [GND]
   [SDA] --- [Analog Pin 4] (The SDA may be different on some devices, e.g. for Arduino Mega the SDA pin is Digital Pin 20)
   [SCL] --- [Analog Pin 5] (The SCL may be different on some devices, e.g. for Arduino Mega the SCL pin is Digital Pin 21)
8. Set the TSL2561Address variable if you connect the the ADDR pin. Unconnected ADDR corresponds to an address of 0x39.
9. Set the token variable to match the Arduino token from the Dashboard.
10. Compile and upload this sketch.
11. Once the Arduino connects to the Dashboard it should automatically update the TSL2561 widget with data.

Code adapted from Adafruit TSL2561 sensorapi example.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <CayenneEthernet.h>

// Virtual Pin of the TSL2561 widget.
#define VIRTUAL_PIN V1

// Address used to read from the TSL2561. This is determined by the ADDR pin on the TSL2561.
// If ADDR is unconnected it means the sensor will use TSL2561_ADDR_FLOAT (0x39) for the address.  See the TSL2561 datasheet for more info.
const int address = TSL2561_ADDR_FLOAT;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(address, 12345);

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
	if (!tsl.begin())
	{
		CAYENNE_LOG("No TSL2561 detected");
	}

	tsl.enableAutoRange(true);
	/* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
	// tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
	// tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}

void loop()
{
	Cayenne.run();
}

// This function is called when the Cayenne widget requests data for the Virtual Pin.
CAYENNE_OUT(VIRTUAL_PIN)
{
	// Send the command to get luminosity.
	sensors_event_t event;
	tsl.getEvent(&event);

	if (event.light)
	{
		// Send the value to Cayenne in lux.
		Cayenne.luxWrite(VIRTUAL_PIN, event.light);
	}
	else
	{
		/* If event.light = 0 lux the sensor is probably saturated
		and no reliable data could be generated! */
		CAYENNE_LOG("No sensor data");
	}
}
