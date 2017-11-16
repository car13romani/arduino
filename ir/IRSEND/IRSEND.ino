#include <IRremote.h> // Biblioteca para controlar o led infravermelho   

  IRsend irsend; 
   
  const int led = 13;    
  const int ledIR = 3;   

  int analogPin = A0;
  int analogResult;
  
  void setup() {   
    pinMode(led, OUTPUT); // saida led     
    pinMode(ledIR ,OUTPUT); // saída do infravermelho   
    Serial.begin(9600);   
 
  }   
  
  void loop(){   
  analogResult = analogRead(analogPin);
  Serial.println(analogResult);
    if (analogResult > 900) {     
    
     digitalWrite(led, HIGH);    
      irsend.sendSony(0x2D, 7);   //codigo para a ser enviado ( lido no printcodes ) e 32 nbits (8 dig no codigo = 2^8 = 32)
      delay(40);
      Serial.println("tira");
      digitalWrite(led, LOW);
      delay(1000);
    }

      delay(50);

    
  }   
