# Cayenne Analog Distance Sensor Example

This sketch shows how to automatically send data to a Analog Distance Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a new Analog Distance Sensor widget.
2. Set the widget to Value Display.
3. Select the Integrated ADC and a pin number.
4. Attach an analog distance sensor to the analog pin on your Arduino matching the selected pin.
   Make sure to use an analog pin, not a digital pin.
   * Schematic:
   ```
   [Ground] -- [Analog Distance Sensor] -- [5V]
                          |
                      Analog Pin
   ```
5. Set the token variable to match the Arduino token from the Dashboard.
6. Compile and upload this sketch.
7. Once the Arduino connects to the Dashboard it should automatically update the Analog Distance Sensor widget with data.