# Cayenne Luminosity Example

This sketch sample file shows how to change the brightness on a LED
using Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. In the Cayenne Dashboard add a new Custom Widget, and select Slider.
2. Select a virtual pin number.
3. Set the slider widget min value to 0 and max value of 255.
4. Set LED_VIRTUAL_PIN to the pin number you selected.
5. Connect the LED's legs to GND, and to a PWM pin (3, 5, 6, 9, 10, and 11 on most Arduino boards).
   Use a 1k resistor if possible.
   * Schematic:
   ```
   [Ground] -- [LED] -- [1k-resistor] -- [PWM Pin]
   ```
6. Set LED_DIGITAL_PIN to the PWM pin number you selected. 
7. Set the token variable to match the Arduino token from the Dashboard.
8. Compile and upload this sketch.
9. Once the Arduino connects to the Dashboard you can use the slider to change LED brightness.