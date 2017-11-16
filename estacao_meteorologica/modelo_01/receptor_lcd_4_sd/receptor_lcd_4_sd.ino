#include <SPI.h>
#include "SdFat.h"
#if SD_SPI_CONFIGURATION >= 3  // Must be set in SdFat/SdFatConfig.h
//
// Pin numbers in templates must be constants.
const uint8_t SOFT_MISO_PIN = 16;
const uint8_t SOFT_MOSI_PIN = 15;
const uint8_t SOFT_SCK_PIN  = 14;
//
// Chip select may be constant or RAM variable.
const uint8_t SD_CHIP_SELECT_PIN = 8;

// SdFat software SPI template
SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> sd;

// Test file.
SdFile file;


//3.52v = 602
//3.85  = 661

#include <Wire.h>
#include "RTClib.h"


#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//#include <DigitalIO.h>
//#include <DigitalPin.h>
//#include <I2cConstants.h>
//#include <nRF24L01.h>
//#include <PinIO.h>
#include <RF24.h>
//#include <RF24_config.h>
//#include <SoftI2cMaster.h>
//#include <SoftSPI.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

RTC_DS3231 rtc;

int dados[4];
int temp = dados[0]; int UR = dados[1]; int bat = dados[3]; int US;
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void){
  display.begin();
  display.setContrast(60); //Ajusta o contraste do display
  //display.clearDisplay();   //Apaga o buffer e o display
 // display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  //display.setCursor(0,0);  //Seta a posição do cursor
  //display.println("Bom dia!");
  
  // delay(2000);
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(100);
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  radio.setCRCLength(RF24_CRC_16);
  radio.setRetries(15,15);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();


  if (!sd.begin(SD_CHIP_SELECT_PIN)) {
      sd.initErrorHalt();
      Serial.println("initialization failed!");
      display.setTextSize(2);
      display.println("SD error");
    return;
  }
  Serial.println("SD Pronto");
  file.open("data.txt", FILE_WRITE);
  file.println();
  file.print("Ano;Mes;Dia;Hora;Min;Seg;Temp;UR;UmidSolo");
  file.println();
  file.close();
  
display.display();
}

void loop(void){
  if (radio.available()){
    bool done = false;
    Serial.println("hora de gravar");
    file.open("data.txt", FILE_WRITE);
          DateTime now = rtc.now();
          display.clearDisplay();   //Apaga o buffer e o display
          display.setTextSize(1);  //Seta o tamanho do texto
          display.setTextColor(BLACK); //Seta a cor do texto
          display.setCursor(0,0);  //Seta a posição do cursor
          display.print("Temp:    ");display.print("UR:");//display.print(" *C");
          display.setCursor(0,10);
          display.setTextSize(2);
          display.print(temp);display.setTextSize(1);display.print("C ");
          display.setTextSize(2);display.setCursor(44,10);display.print(UR);display.setTextSize(1);display.print("%");
          display.setCursor(0,27);
          display.setTextSize(1);
          display.print("US:");display.print(US);display.print(" %");
          display.setCursor(53,30);
          display.print("");display.print(now.hour(), DEC);
          display.print(":");display.print(now.minute(), DEC);
          display.setCursor(0,40);display.print(bat);
          display.setCursor(23,40);
          display.print("");display.print(now.day(), DEC);
          display.print("/");display.print(now.month(), DEC);
          display.print("/");display.print(now.year(), DEC);
          display.display();
          
          file.print(now.year(), DEC);
          file.print((';'));
          file.print(now.month(), DEC);
          file.print((';'));
          file.print(now.day(), DEC);
          file.print((';'));
          file.print(now.hour(), DEC);
          file.print((';'));
          file.print(now.minute(), DEC);
          file.print((';'));
          file.print(now.second(), DEC);
          file.print((';'));
          file.print(temp);
          file.print((';'));
          file.print(UR);
          file.print((';'));
          file.println(US);
          file.close();
    
    while (!done)
    {   
          
       //dataFile = SD.open("test.txt", FILE_WRITE);
      //  if (dataFile) {
          
          done = radio.read( dados, sizeof(dados) );
          temp = dados[0]; UR = dados[1]; bat = dados[3];

          US = map(dados[2], 1023, 100, 0, 100);
          if(temp != 0 and UR != 0){
          Serial.print("Temperatura:  "); Serial.print(temp);
          Serial.print("    Umidade Relativa:  "); Serial.print(UR);
          Serial.print("    Umidade solo:  "); Serial.println(US);
          /*int ano = (now.year(), DEC);
          int mes = (now.month(), DEC);
          int dia = (now.day(), DEC);
          int hora = (now.hour(), DEC);
          int minu = (now.minute(), DEC);
          int seg = (now.second(), DEC);*/
   /*       
          display.clearDisplay();   //Apaga o buffer e o display
          display.setTextSize(1);  //Seta o tamanho do texto
          display.setTextColor(BLACK); //Seta a cor do texto
          display.setCursor(0,0);  //Seta a posição do cursor
          display.print("Temp:    ");display.print("UR:");//display.print(" *C");
          display.setCursor(0,10);
          display.setTextSize(2);
          display.print(temp);display.setTextSize(1);display.print("C ");
          display.setTextSize(2);display.setCursor(44,10);display.print(UR);display.setTextSize(1);display.print("%");
          display.setCursor(0,27);
          display.setTextSize(1);
          display.print("US:");display.print(US);display.print(" %");
          display.setCursor(53,30);
          display.print("");display.print(now.hour(), DEC);
          display.print(":");display.print(now.minute(), DEC);
          display.setCursor(0,40);display.print(bat);
          display.setCursor(23,40);
          display.print("");display.print(now.day(), DEC);
          display.print("/");display.print(now.month(), DEC);
          display.print("/");display.print(now.year(), DEC);
          
         display.display();
         file.print(now.year(), DEC);
          file.print((';'));
          file.print(now.month(), DEC);
          file.print((';'));
          file.print(now.day(), DEC);
          file.print((';'));
          file.print(now.hour(), DEC);
          file.print((';'));
          file.print(now.minute(), DEC);
          file.print((';'));
          file.print(now.second(), DEC);
          file.print((';'));
          file.print(temp);
          file.print((';'));
          file.print(UR);
          file.print((';'));
          file.println(US);
          file.close();
     
                
*/



        
     // }
      }
   }
  }

  
}
#else  // SD_SPI_CONFIGURATION >= 3
#error SD_SPI_CONFIGURATION must be set to 3 in SdFat/SdFatConfig.h
#endif  //SD_SPI_CONFIGURATION >= 3

