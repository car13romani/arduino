# Cayenne BMP180 Example

This sketch shows how to send luminosity data to a BMP180 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. Install the Adafruit Unified Sensor library (https://github.com/adafruit/Adafruit_Sensor) from the Arduino Library Manager.
2. Install the Adafruit BMP085 Unified library (https://github.com/adafruit/Adafruit_BMP085_Unified) from the Arduino Library Manager.
3. In the Cayenne Dashboard add a new BMP180 widget.
4. Set the widget to Value Display.
5. Select Virtual Pins and select virtual channels for the barometer and temperature.
6. Set BAROMETER_PIN to the pin number you selected for the barometer.
7. Set TEMPERATURE_PIN to the pin number you selected for the temperature.
8. Attach a BMP180 to your Arduino.
   * Schematic:
   ```
   BMP180    Arduino
   [VDD] --- [3V3]
   [GND] --- [GND]
   [SDA] --- [Analog Pin 4] (The SDA may be different on some devices, e.g. for Arduino Mega the SDA pin is Digital Pin 20)
   [SCL] --- [Analog Pin 5] (The SCL may be different on some devices, e.g. for Arduino Mega the SCL pin is Digital Pin 21)
   ```
9. Set the token variable to match the Arduino token from the Dashboard.
10. Compile and upload this sketch.
11. Once the Arduino connects to the Dashboard it should automatically update the BMP180 widget with data.