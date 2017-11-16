# Cayenne Valve Switch Example

This sketch shows how to set up a Valve Switch with Cayenne. The Arduino cannot
drive a valve because it does not output the needed current. As a result, in order
to make this example work, various electronic components are necessary to connect
the valve. To keep it simple, you will need an external power source, transistor (eg. TIP120),
diode (eg. 1N4001), and a 1k ohm resistor. Alternatively you could also use a relay switch to 
connect the valve.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a new Valve Switch Widget.
2. Select a digital pin number. Do not use digital pins 0 or 1 since those conflict with the use of Serial.
3. Set up your valve schematic and attach it to the selected pin.
4. Set the token variable to match the Arduino token from the Dashboard.
5. Compile and upload this sketch.
6. Once the Arduino connects to the Dashboard you can toggle the Valve Switch.

Notice that there isn't much coding involved to interact with the digital pins.
Most of it is handled automatically from the Cayenne library.

## Example Schematic
http://www.bc-robotics.com/wp-content/uploads/2015/07/sketch1-1024x919.jpg