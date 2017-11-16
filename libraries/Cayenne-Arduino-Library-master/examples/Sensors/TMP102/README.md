# Cayenne TMP102 Example

This sketch shows how to send temperature data to a TMP102 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a new TMP102 widget.
2. Set the widget to Value Display.
3. Select Virtual Pins and a virtual pin number.
4. Set VIRTUAL_PIN to the pin number you selected.
5. Attach a TMP102 to your Arduino.
   * Schematic:
   ```
   TMP102    Arduino
   [VCC] --- [3V3]
   [GND] --- [GND]
   [ADD0] -- [GND]
   [SDA] --- [Analog Pin 4] (The SDA may be different on some devices, e.g. for Arduino Mega the SDA pin is Digital Pin 20)
   [SCL] --- [Analog Pin 5] (The SCL may be different on some devices, e.g. for Arduino Mega the SCL pin is Digital Pin 21)
   ```
6. Set the tmp102Address variable to match the ADD0. ADD0 connected to GND corresponds to an address of 0x48.
7. Set the token variable to match the Arduino token from the Dashboard.
8. Compile and upload this sketch.
9. Once the Arduino connects to the Dashboard it should automatically update the TMP102 widget with data.