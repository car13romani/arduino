# Cayenne VCNL4000 Example

This sketch shows how to send luminosity data to a VCNL4000 Sensor in the Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a new VCNL4000 widget.
2. Set the widget to Value Display.
3. Select Virtual Pins and select virtual channels for the distance and luminosity.
4. Set DISTANCE_PIN to the pin number you selected for the distance.
5. Set LUMINOSITY_PIN to the pin number you selected for the luminosity.
6. Attach a VCNL4000 to your Arduino.
   * Schematic:
   ```
   VCNL4000    Arduino
   [VDD] ------- [3V3]
   [IR Anode] -- [5V]
   [GND] ------- [GND]
   [SDA] ------- [Analog Pin 4] (The SDA may be different on some devices, e.g. for Arduino Mega the SDA pin is Digital Pin 20)
   [SCL] ------- [Analog Pin 5] (The SCL may be different on some devices, e.g. for Arduino Mega the SCL pin is Digital Pin 21)
   ```
7. Set the token variable to match the Arduino token from the Dashboard.
8. Compile and upload this sketch.
9. Once the Arduino connects to the Dashboard it should automatically update the VCNL4000 widget with data.