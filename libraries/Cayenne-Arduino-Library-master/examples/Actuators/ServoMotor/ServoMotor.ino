/*
Cayenne Servo Motor Example

This sketch sample file shows how to connect a Servo Motor with Cayenne Library.
For this example we are going to use a slider widget and the servo will move
depending on the slider value.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
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
*/

#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneEthernet.h>
#define SERVO_VIRTUAL_PIN 1
#define SERVO_DIGITAL_PIN 4

// servo util lib
#include <Servo.h>
Servo s1;

// a flag to keep track of servos last position
double lastPosition = 0;

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
  Serial.begin(9600);
  Cayenne.begin(token);

  s1.attach(SERVO_DIGITAL_PIN);
}

CAYENNE_IN(SERVO_VIRTUAL_PIN)
{
  // get value sent from dashboard
  double currentValue = getValue.asDouble();
  int position = currentValue * 200;
  // actually move the servo to the specified position
  s1.write(position);

  //update last position
  lastPosition = currentValue;
}

void loop()
{
  Cayenne.run();
}
