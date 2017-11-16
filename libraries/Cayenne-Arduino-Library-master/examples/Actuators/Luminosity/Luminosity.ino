/*
Cayenne Luminosity Example

This sketch sample file shows how to change the brightness on a LED
using Cayenne Dashboard.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Custom Widget, and select Slider.
2. Select a virtual pin number.
3. Set the slider widget min value to 0 and max value of 255.
4. Set LED_VIRTUAL_PIN to the pin number you selected.
5. Connect the LED's legs to GND, and to a PWM pin (3, 5, 6, 9, 10, and 11 on most Arduino boards).
   Use a 1k resistor if possible.
   Schematic:
   [Ground] -- [LED] -- [1k-resistor] -- [PWM Pin]
6. Set LED_DIGITAL_PIN to the PWM pin number you selected. 
7. Set the token variable to match the Arduino token from the Dashboard.
8. Compile and upload this sketch.
9. Once the Arduino connects to the Dashboard you can use the slider to change LED brightness.
*/


#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneEthernet.h>

#define LED_VIRTUAL_PIN 1
#define LED_DIGITAL_PIN 3

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
  Serial.begin(9600);
  Cayenne.begin(token);
}

CAYENNE_IN(LED_VIRTUAL_PIN)
{
  // get value sent from dashboard
  int currentValue = getValue.asInt(); // 0 to 255
  analogWrite(LED_DIGITAL_PIN, currentValue); // analogWrite accepts a value from 0 to 255
}

void loop()
{
  Cayenne.run();
}
