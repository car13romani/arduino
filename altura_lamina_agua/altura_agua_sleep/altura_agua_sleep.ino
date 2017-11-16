#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include "SdFat.h"
#include <avr/sleep.h>
#define __AVR_ATmega328P__
#include <avr/wdt.h>
volatile int sleep_count = 0;
const int interval = 1; // Interval in minutes between waking
// and doing tasks.
const int sleep_total = (interval*60)/8;

int dia;
int mes;
int ano;
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
  wdt_disable();
  watchdogOn(); // Turn on the watch dog timer.
  ADCSRA = ADCSRA & B01111111;
  ACSR = B10000000;
  DIDR0 = DIDR0 | B00111111;
  
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

}

void loop() {
    
  
  wdt_disable();
goToSleep();
if (sleep_count == sleep_total) {

// CODE TO BE EXECUTED PERIODICALLY
for(int i=0;i<10;i++){

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
  delay(100);
 
   }
  
  DateTime now = rtc.now();
  dist = (somatorio/divisor);
  ano = ("%04d",now.year());
  mes = ("%02d",now.month());
  dia = ("%02d",now.day());
  hora = ("%02d", now.hour());
  minuto = ("%02d", now.minute());
  segundo = ("%02d", now.second());
  file.open("arquivo02.txt", FILE_WRITE);
  file.print(ano); file.print(('\t'));
  file.print(mes); file.print(('\t'));
  file.print(dia); file.print(('\t'));
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

somatorio = 0;
divisor = 0;

sleep_count = 0;
}
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
void goToSleep()   
{
// The ATmega328 has five different sleep states.
// See the ATmega 328 datasheet for more information.
// SLEEP_MODE_IDLE -the least power savings 
// SLEEP_MODE_ADC
// SLEEP_MODE_PWR_SAVE
// SLEEP_MODE_STANDBY
// SLEEP_MODE_PWR_DOWN -the most power savings
// I am using the deepest sleep mode from which a
// watchdog timer interrupt can wake the ATMega328

set_sleep_mode(SLEEP_MODE_STANDBY); // Set sleep mode.
sleep_enable(); // Enable sleep mode.
sleep_mode(); // Enter sleep mode.
// After waking from watchdog interrupt the code continues
// to execute from this point.

sleep_disable(); // Disable sleep mode after waking.
                     
}

void watchdogOn() {
  
// Clear the reset flag, the WDRF bit (bit 3) of MCUSR.
MCUSR = MCUSR & B11110111;
  
// Set the WDCE bit (bit 4) and the WDE bit (bit 3) 
// of WDTCSR. The WDCE bit must be set in order to 
// change WDE or the watchdog prescalers. Setting the 
// WDCE bit will allow updtaes to the prescalers and 
// WDE for 4 clock cycles then it will be reset by 
// hardware.
WDTCSR = WDTCSR | B00011000; 

// Set the watchdog timeout prescaler value to 1024 K 
// which will yeild a time-out interval of about 8.0 s.
WDTCSR = B00100001;

// Enable the watchdog timer interupt.
WDTCSR = WDTCSR | B01000000;
MCUSR = MCUSR & B11110111;

}

ISR(WDT_vect)
{
sleep_count ++; // keep track of how many sleep cycles
// have been completed.
}
