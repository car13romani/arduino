#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include "SdFat.h"
//#include <avr/sleep.h>
#define __AVR_ATmega328P__
//#include <avr/wdt.h>
 

//#include <avr/wdt.h>
String arquivo;
int dia;
int mes;
int hora;
int minuto;
int segundo;
long int time0 = 0;
long int time1 = 0;
long int somatorio = 0;
long int divisor = 0;
long int dist = 0;

const int TriggerPin = A1;
const int EchoPin = A0;
long Duracion = 0;

const int SD_CHIP_SELECT_PIN = 10;
SdFat sd;
SdFile file;

RTC_DS3231 rtc;


void setup() {
  pinMode(TriggerPin,OUTPUT);
  pinMode(EchoPin,INPUT);

   Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!sd.begin(SD_CHIP_SELECT_PIN)) {
      sd.initErrorHalt();
      Serial.println("initialization failed!");
    return;
  }
  Serial.println("SD Pronto");
  DateTime now = rtc.now();
   dia = now.day();
   mes = now.month();
   time0 = millis();
 // wdt_reset();
   //wdt_disable();
  

}

void loop() {
  
  // wdt_disable(); 
    
  time1 = millis();
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
   
  Duracion = pulseIn(EchoPin,HIGH);
  long Distancia_mm = fDistancia(Duracion);
  
  
  somatorio = somatorio + Distancia_mm;
  divisor++;
  Serial.println(Distancia_mm);

    
  if(time1 - time0 >= 60000){
      DateTime now = rtc.now();
      

      dist = (somatorio/divisor);
      hora = ("%02d", now.hour());
      minuto = ("%02d", now.minute());
      segundo = ("%02d", now.second());
      file.open("arquivo07.txt", FILE_WRITE);
      file.print(now.year()); file.print(('\t'));
      file.print(now.month()); file.print(('\t'));
      file.print(now.day()); file.print(('\t'));
      file.print(hora); file.print(('\t'));
      file.print(minuto); file.print(('\t'));
      file.print(segundo); file.print(('\t'));
      file.print(dist);
      file.println();
      file.close();
      Serial.print(now.year()); Serial.print(('\t'));
      Serial.print(now.month()); Serial.print(('\t'));
      Serial.print(now.day()); Serial.print(('\t'));
      Serial.print(hora); Serial.print(('\t'));
      Serial.print(minuto); Serial.print(('\t'));
      Serial.print(segundo); Serial.print(('\t'));
      Serial.print(dist);
      Serial.println();

      
      dia = now.day();
      mes = now.month();
      time0 = millis();
      somatorio = 0;
      divisor = 0;
    
   }
   delay(400);


}

// Función para calcular la distancia
long fDistancia(long tiempo)
{
// Calculamos la distancia en mm
// ((tiempo)*(Velocidad del sonido)/ el camino se hace dos veces) 
 
long DistanceCalc; // Variable para los cálculos
DistanceCalc = (tiempo /2.9) / 2; // Cálculos en milímetros
// DistanceCalc = (tiempo /29) / 2; // Cálculos en centímetros
// DistanceCalc = (tiempo / 74) / 2; // Cálculos en pulgadas
return DistanceCalc; // Devolvemos el calculo
}
