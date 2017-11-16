#include <SPI.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include "TinyGPS.h"
int timeS = 0;
int timeM = 0;

File dataFile;
TinyGPS gps;

int unoRxPin = 3; // connected to Tx pin of the GPS
int unoTxPin = 2; // connected to Rx pin of the GPS
SoftwareSerial ss(unoRxPin, unoTxPin);

long startMillis;
long secondsToFirstLocation = 0;

int botao = 7;

void setup()   
{
  Serial.begin(9600);
  pinMode(botao, INPUT);
  ss.begin(9600);
  startMillis = millis();
  Serial.print("Inicializando cartao SD...");
  delay(2000);
  if (!SD.begin(10)) {
    while(!SD.begin(10)){
      Serial.println("Falha cartao SD  ");
      delay(100);
    }    
  }

Serial.println("ok");
}

void loop()
{
  
    bool newData = false;
  unsigned long chars = 0;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      int c = ss.read();
      ++chars;
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    // we have a location fix so output the lat / long and time to acquire
    if(secondsToFirstLocation == 0){
      secondsToFirstLocation = (millis() - startMillis) / 1000;
    }
    dataFile = SD.open("test.txt", FILE_WRITE);
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("Lat=");
    dataFile.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 8);
    dataFile.print(";");
    Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 12);
    

    Serial.print("Long=");
    dataFile.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 8);
    Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 12);
    dataFile.print(";");
    Serial.println(gps.f_speed_kmph());
    dataFile.print(gps.f_speed_kmph());
    dataFile.print(";");
    dataFile.print(gps.f_altitude());
    dataFile.print(";");
    
    timeS++;
    if(timeS > 59){
      timeS = 0;
      timeM++;
    }

    //display.print(secondsToFirstLocation);
    dataFile.print(timeM);
    dataFile.print(";");
    dataFile.print(timeS);
    dataFile.print(";"); 
    dataFile.println();
    dataFile.close();

Serial.println(digitalRead(botao));
    if(digitalRead(botao) == HIGH){
      Serial.println("tirar sd");
      delay(10000);
      
    }
    
  }
  
  if (chars == 0){
    // if you haven't got any chars then likely a wiring issue
         // set cursor to column 0, row 0 (the first row)
    Serial.println("Sem GPS, cheque conexao");
  }
  else if(secondsToFirstLocation == 0){

    long seconds = (millis() - startMillis) / 1000;
    
    for(int i = 0; i < seconds % 4; ++i){
    }
    
  }


}
