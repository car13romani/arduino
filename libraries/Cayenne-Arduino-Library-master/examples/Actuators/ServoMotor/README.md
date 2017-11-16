## Cayenne Servo Motor Example

This sketch sample file shows how to connect a ServoMotor with Cayenne Library.
For this example we are going to use a slider widget and the servo will move
depending on the slider value.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. Install the Servo library from the Arduino Library Manager.
2. In the Cayenne Dashboard add a new Custom Widget, and select Slider.
3. Select a Virtual pin number.
4. Set min value to 0 and max value of 1.
5. Set SERVO_VIRTUAL_PIN to the pin number you selected.
6. Connect the Servo's legs to GND, VCC (5.0), and a Digital pin.
7. Set SERVO_DIGITAL_PIN to the pin number you selected.
8. Set the token variable to match the Arduino token from the Dashboard.
9. Compile and upload this sketch.
10. Once the Arduino connects to the Dashboard you can use the slider to change servo position.

### Where to go from here?
Another use case for the servo is the use of a Button. By turning on the button,
the servo can be set to a specific position and back when it's off.
