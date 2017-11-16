# Cayenne Motor Switch Actuator Example

This sketch shows how to setup a Motor Switch with Cayenne. The Arduino cannot
drive a motor because it does not output the needed current. As a result, in order
to make this example work, various electronic components are necessary to drive
the DC motor. To keep it simple, the we will need a **transistor (PN2222)**,
**diode (1N4001)**, and a **270 ohm resistor**.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a Button using Custom Widget.
2. Select a virtual pin number.
3. Set VIRTUAL_PIN to the pin number you selected.
4. Set up your motor schematic and attach it to a PWM pin.
5. Set the motorPin variable to the PWM pin number you selected.
6. Set the token variable to match the Arduino token from the Dashboard.
7. Compile and upload this sketch.
8. Once the Arduino connects to the Dashboard you can toggle the Motor switch.

We use the virtual pin to receive data from the dashboard to enable and disable the motor.

## Example Schematic
https://cdn-learn.adafruit.com/assets/assets/000/002/346/medium640/learn_arduino_breadboard.jpg?1396782072