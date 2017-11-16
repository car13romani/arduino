#include <Servo.h>
Servo mot1;
//unsigned long t;
unsigned long t1;

//t = millis();

//Serial.println(t);

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 2; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int m1 = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  mot1.attach(2);
  mot1.write(0);
}

void loop() {
  sensorValue = analogRead(analogInPin);

  t1 = map(sensorValue, 0, 1023, 1000, 6000);
  
  mot1.write(0);
  delay(t1);
  mot1.write(150);
  delay(t1);
  Serial.println(t1);
}
