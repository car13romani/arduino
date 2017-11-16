#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#include "TinyGPS.h"
int timeS = 0;
int timeM = 0;

TinyGPS gps;

int unoRxPin = 2 ; // connected to Tx pin of the GPS
int unoTxPin = 3; // connected to Rx pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);
int backLight = 13;    // pin 13 will control the backlight

long startMillis;
long secondsToFirstLocation = 0;

// pin 8 - Serial clock out (SCLK)
// pin 9 - Serial data out (DIN)
// pin 10 - Data/Command select (D/C)
// pin 11 - LCD chip select (CS/CE)
// pin 12 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

void setup()   
{
  Serial.begin(9600);
  display.begin();
  display.setContrast(50); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(4);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(8,8);  //Seta a posição do cursor
  display.println("GPS");  
  display.display();
  
  ss.begin(9600);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  startMillis = millis();
  delay(200);
}

void loop()
{
  
    display.clearDisplay();   //Apaga o buffer e o display
    display.setTextSize(1);  //Seta o tamanho do texto
    display.setTextColor(BLACK); //Seta a cor do texto
    bool newData = false;
  unsigned long chars = 0;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
//  Serial.println("Antes do FOR");
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
//    Serial.println("Depois do FOR   -   Antes do While");
    while (ss.available())
    {
//      Serial.println("Depois do While   -   Antes do IF");      
      //Serial.println("deu");
      int c = ss.read();
      ++chars;
      if (gps.encode(c)){
//        Serial.println("Dentro do IF");      
        newData = true;
      }
    }
  }

  if (newData)
  {
    Serial.println("NEW DATA");
    // we have a location fix so output the lat / long and time to acquire
    if(secondsToFirstLocation == 0){
      secondsToFirstLocation = (millis() - startMillis) / 1000;
    }

    float flat, flon, vel;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    //gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
    gps.f_speed_kmph();
    display.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
    display.print("L=");
    Serial.print("Lat=");
    display.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 7);
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 12);
    
    

    display.setCursor(0,10);
    display.print("O=");
    Serial.print("Long=");
    display.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 7);
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 12);
    
    
    timeS++;
    if(timeS > 59){
      timeS = 0;
      timeM++;
    }

    display.setCursor(0,20);
    //display.print("Vel=");
    //display.print(vel == TinyGPS::GPS_INVALID_F_SPEED ? 0.0 : vel, 5);
    display.print("V: "); display.print(gps.f_speed_kmph());
    
    display.setCursor(0,30);
    display.print("Tempo=");
    //display.print(secondsToFirstLocation);
    display.print(timeM);
    display.print(":");
    display.print(timeS);
    display.setCursor(0,40); 
    display.print("Sat= "); display.print(gps.satellites());
  }
  
  if (chars == 0){
    // if you haven't got any chars then likely a wiring issue
    display.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
    display.print("Sem GPS, cheque conexao");
    Serial.println("Sem GPS, cheque conexao");
  }
  else if(secondsToFirstLocation == 0){
    // if you have received some chars but not yet got a fix then indicate still searching and elapsed time
    display.clearDisplay();  // start with a blank screen

    long seconds = (millis() - startMillis) / 1000;
    
    display.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
    display.print("Procurando ");
    Serial.println("Procurando ");
    for(int i = 0; i < seconds % 4; ++i){
      display.print(".");
    }
    
    display.setCursor(0,8);
    display.print("Tempo: ");
    display.print(seconds);
    display.print("s");
  }



    display.display();
    
    //delay(1000);
    

    
    
    
    
    
  // Codigo adicional
}
