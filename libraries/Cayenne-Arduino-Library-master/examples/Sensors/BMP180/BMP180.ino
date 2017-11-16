/*
Cayenne BMP180 Example

This sketch shows how to send luminosity data to a BMP180 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Install the Adafruit Unified Sensor library (https://github.com/adafruit/Adafruit_Sensor) from the Arduino Library Manager.
2. Install the Adafruit BMP085 Unified library (https://github.com/adafruit/Adafruit_BMP085_Unified) from the Arduino Library Manager.
3. In the Cayenne Dashboard add a new BMP180 widget.
4. Set the widget to Value Display.
5. Select Virtual Pins and select virtual pins for the barometer and temperature.
6. Set BAROMETER_PIN to the pin number you selected for the barometer.
7. Set TEMPERATURE_PIN to the pin number you selected for the temperature.
8. Attach a BMP180 to your Arduino.
   Schematic:
   BMP180    Arduino
   [VDD] --- [3V3]
   [GND] --- [GND]
   [SDA] --- [Analog Pin 4] (The SDA may be different on some devices, e.g. for Arduino Mega the SDA pin is Digital Pin 20)
   [SCL] --- [Analog Pin 5] (The SCL may be different on some devices, e.g. for Arduino Mega the SCL pin is Digital Pin 21)
9. Set the token variable to match the Arduino token from the Dashboard.
10. Compile and upload this sketch.
11. Once the Arduino connects to the Dashboard it should automatically update the BMP180 widget with data.
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <CayenneEthernet.h>

// Virtual Pins of the BMP180 widget.
#define BAROMETER_PIN V1
#define TEMPERATURE_PIN V2

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10180);
bool bmpSensorDetected = true;

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
	if (!bmp.begin())
	{
		CAYENNE_LOG("No BMP sensor detected");
		bmpSensorDetected = false;
	}
}

void loop()
{
	Cayenne.run();
}

// This function is called when the Cayenne widget requests data for the barometer's Virtual Pin.
CAYENNE_OUT(BAROMETER_PIN)
{
	if (bmpSensorDetected)
	{
		// Send the command to get data.
		sensors_event_t event;
		bmp.getEvent(&event);

		if (event.pressure)
		{
			// Send the value to Cayenne in hectopascals.
			Cayenne.hectoPascalWrite(BAROMETER_PIN, event.pressure);
		}
	}
	else
	{
		CAYENNE_LOG("No BMP sensor detected");
	}
}

// This function is called when the Cayenne widget requests data for the temperature's Virtual Pin.
CAYENNE_OUT(TEMPERATURE_PIN)
{
	if (bmpSensorDetected)
	{
		float temperature;
		bmp.getTemperature(&temperature);
		// Send the value to Cayenne in Celsius.
		Cayenne.celsiusWrite(TEMPERATURE_PIN, temperature);
	}
	else
	{
		CAYENNE_LOG("No BMP sensor detected");
	}
}