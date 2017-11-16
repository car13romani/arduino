# Cayenne TSL2561 Example

This sketch shows how to send luminosity data to a TSL2561 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. Install the Adafruit Unified Sensor library (https://github.com/adafruit/Adafruit_Sensor) from the Arduino Library Manager.
2. Install the Adafruit TSL2561 library (https://github.com/adafruit/Adafruit_TSL2561) from the Arduino Library Manager.
3. In the Cayenne Dashboard add a new TSL2561 widget.
4. Set the widget to Value Display.
5. Select Virtual Pins and a virtual pin number.
6. Set VIRTUAL_PIN to the pin number you selected.
7. Attach a TSL2561 to your Arduino.
   * Schematic:
   ```
   TSL2561    Arduino
   [VCC] --- [3V3]
   [GND] --- [GND]
   [SDA] --- [Analog Pin 4] (The SDA may be different on some devices, e.g. for Arduino Mega the SDA pin is Digital Pin 20)
   [SCL] --- [Analog Pin 5] (The SCL may be different on some devices, e.g. for Arduino Mega the SCL pin is Digital Pin 21)
   ```
8. Set the TSL2561Address variable if you connect the the ADDR pin. Unconnected ADDR corresponds to an address of 0x39.
9. Set the token variable to match the Arduino token from the Dashboard.
10. Compile and upload this sketch.
11. Once the Arduino connects to the Dashboard it should automatically update the TSL2561 widget with data.