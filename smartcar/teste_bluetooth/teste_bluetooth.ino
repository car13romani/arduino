//Programa : Modulo Bluetooth HC-06 - Leds
//Autor : Adilson Thomsen

#include <Servo.h>
 
//Armazena o caracter recebido
char buf;

int MotorRight2=11;
int MotorRight1=10;
int MotorLeft2=8;
int MotorLeft1=9;
int counter=0;
int delay_servo = 300;
const int irReceiverPin = 2; //Infrared recive connect to pin 2
Servo myservo; // set myservo
 
void setup()
{
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // pin 8 (PWM)
  pinMode(MotorRight2, OUTPUT);  // pin 9 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // pin 10 (PWM) 
  pinMode(MotorLeft2,  OUTPUT);  // pin 11 (PWM)
  /*
  irrecv.enableIRIn();     // start infrared encode
  Serial.println("esperando comando");
   pinMode(SensorLeft, INPUT); //define left sensor 
  pinMode(SensorMiddle, INPUT);//define middle sensor 
  pinMode(SensorRight, INPUT); //define right sensor 
  //digitalWrite(2,HIGH);
  pinMode(echoPin, INPUT); // define ultrasonic recive pin
  pinMode(trigPin, OUTPUT); // define ultrasonic echo pin 
  */
  myservo.attach(6); // deine servo motor pin

  Serial.println("pronto");
}

void advance(int a) // go forward
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  delay(a * 100); 
}
void right(int b) //turn right (single wheel)
{
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,LOW);
  delay(b * 100);
}
void left(int c) //turn left(single wheel) 
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,LOW);
  delay(c * 100);
}
void turnR(int d) //turn right (double wheels)
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  delay(d * 100);
}
void turnL(int e) //turn left (double wheels)
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);
  delay(e * 100);
} 
void stopp(int f) //stop
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,LOW);
  delay(f * 100);
}
void back(int g) //go back
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);;
  delay(g * 100); 
}
 
void loop()
{
  int aux;
  while(Serial.available() > 0)
  {
    buf = Serial.read();
    //Caso seja recebido R, acende o led vermelho
    if (buf == 'f')
    {
      advance(aux);
      Serial.println("LED ligado !");
    }
    //Caso seja recebido G, acende o led verde
    else if (buf == 'b')
    {
      back(aux);
      Serial.println("LED desligado !");
    }
    else if (buf == 'l')
    {
      left(aux);
      Serial.println("LED desligado !");
    }
    else if (buf == 'r')
    {
      right(aux);
      Serial.println("LED desligado !");
    }

  }
}
