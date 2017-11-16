/*
Cayenne Relay Switch Example

This sketch sample file shows how to connect a Relay Switch.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. In the Cayenne Dashboard add a new Custom Widget, and select Button.
2. Select a Virtual pin number.
3. Set VIRTUAL_PIN to the pin number you selected.
4. Connect the Relay Switch to a digital pin.
5. Set RELAY_DIGITAL_PIN to the digital pin number you selected.
6. Set the token variable to match the Arduino token from the Dashboard.
7. Compile and upload this sketch.
8. Once the Arduino connects to the Dashboard use the button widget to
   turn on/off an LED wired through the Relay.
*/


#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneEthernet.h>
#define VIRTUAL_PIN 1
#define RELAY_DIGITAL_PIN 4

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
  // set digital pin to output
  pinMode(RELAY_DIGITAL_PIN, OUTPUT);

  Serial.begin(9600);
  Cayenne.begin(token);
}

CAYENNE_IN(VIRTUAL_PIN)
{
  // get value sent from dashboard
  int currentValue = getValue.asInt(); // 0 to 1

  // assuming you wire your relay as normally open
  if (currentValue == 0) {
    digitalWrite(RELAY_DIGITAL_PIN, HIGH);
  } else {
    digitalWrite(RELAY_DIGITAL_PIN, LOW);
  }
}

void loop()
{
  Cayenne.run();
}
