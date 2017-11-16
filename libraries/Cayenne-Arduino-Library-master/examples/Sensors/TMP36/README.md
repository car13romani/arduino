# Cayenne TMP36 Example

This sketch shows how to send temperature data to a TMP36 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a new TMP36 widget.
2. Set the widget to Value Display.
3. Select Virtual Pins and a virtual pin number.
4. Set VIRTUAL_PIN to the pin number you selected.
5. Attach a TMP36 to an analog pin on your Arduino. Make sure to use an analog pin, not a digital pin.
   * Schematic:
   ```
   [Ground] -- [TMP36] -- [5V]
                  |
              Analog Pin
   ```
6. Set the tmpPin variable to match the pin used to connect the TMP36.
7. Set the voltage variable to match the voltage used to connect the TMP36.
8. Set the token variable to match the Arduino token from the Dashboard.
9. Compile and upload this sketch.
10. Once the Arduino connects to the Dashboard it should automatically update the TMP36 widget with data.