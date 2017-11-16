# Cayenne DS18B20 Example

This sketch shows how to send temperature data to a DS18B20 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. Install the OneWire library (http://www.pjrc.com/teensy/td_libs_OneWire.html) from the Arduino Library Manager.
2. Install the DallasTemperature library (http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library#Code.2FLibrary) from the Arduino Library Manager.
3. In the Cayenne Dashboard add a new DS18B20 widget.
4. Set the widget to Value Display.
5. Select Virtual Pins and a virtual pin number.
6. Set VIRTUAL_PIN to the pin number you selected.
7. Attach a DS18B20 to an digital pin on your Arduino.
   * Schematic:
   ```
   [Ground] -- [DS18B20] -- [4.7k resistor] -- [5V]
                   |
              Digital Pin
   ```
8. Set the tmpPin variable to match the pin used to connect the DS18B20.
9. Set the token variable to match the Arduino token from the Dashboard.
10. Compile and upload this sketch.
11. Once the Arduino connects to the Dashboard it should automatically update the DS18B20 widget with data.