#include <SoftwareSerial.h>

int bitrate = 9600;
int imprime = 0;
SoftwareSerial mySerial = SoftwareSerial(3,2);

void setup()
{
//mySerial.begin(bitrate);
Serial.begin(9600);
mySerial.begin(9600);
}

 void loop()
{
  
//imprime = (mySerial.read());
//Serial.println(imprime); 
while(mySerial.available() > 0){ 
Serial.println(mySerial.read(), bitrate);
delay(100);
}
}
