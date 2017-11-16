// Código desenvolvido e testado por Carlos Alexandre Romani
// Laboratório de Sistemas Inteligentes e Modelagem - LabSIM
// Estação meteorológica versão 2
//  12/10/2016


#include <SPI.h>
#include "SdFat.h"
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <RF24.h>
#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#if SD_SPI_CONFIGURATION >= 3  // Must be set in SdFat/SdFatConfig.h
const uint8_t SOFT_MISO_PIN = 3;
const uint8_t SOFT_MOSI_PIN = 4;
const uint8_t SOFT_SCK_PIN  = 5;
const uint8_t SD_CHIP_SELECT_PIN = 6;
SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> sd;
SdFile file;

Adafruit_PCD8544 display = Adafruit_PCD8544(25, 27, 29, 31, 33);

RTC_DS3231 rtc;

int dados[15];
RF24 radio(48,49);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

#define pinBL 23
#define pinL 22
#define pinUS1 A0
#define pinUS2 A1
#define pinUS3 A2
#define pinTS A3
#define pinDHT1 A4
#define pinDHT2 A5
#define pinANE A8
#define pinLDR A9
#define pinPLUVI1 A10
#define pinPLUVI2 A11
#define pinBAT A7

#define DHTTYPE DHT22 // DHT 22
DHT dht1(pinDHT1, DHTTYPE);
DHT dht2(pinDHT2, DHTTYPE);

OneWire oneWire(pinTS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

float PREC = 0;   //mm de chuva
float VV = 0;    //m/s
int const_anemometro = 5;
int st = 0;
int c1 = 0; int c2 = 0;
float area = 0.1418;  //metros quadrados
float vol1 = 0.00694; // litros
float vol2 = 0.00694;
long int time0 = 0;
long int time1 = 0;
long int timea0 = 0;
long int timea1 = 0;
int cc = 0;
int i = 0;
int cV = 0; int stV = 0; int V = 0;
int US1 = 0; int US2 = 0; int US3 = 0; int LUM = 0; float BAT = 0;
int dia = 0; int mes = 0; int ano = 0;
float t1 = 0; float t2 = 0; float ts = 0;

//------------------------------------------------------------  FUNCOES  ----------------------------------------

void armazena(){
   DateTime now = rtc.now();
   if(now.day() > dia or now.month() > mes){
    c1 = 0;
    c2 = 0;
   }

  t2 = dht2.readTemperature();
  t1 = dht1.readTemperature();

  sensors.requestTemperatures();
  ts = sensors.getTempC(sensor1);

   VV = (V*0.578)/60;
   Serial.print("       ");
   Serial.print(VV);
   V = 0;
   ano = ("%04d",now.year());
   mes = ("%02d",now.month());
   dia = ("%02d",now.day());
   
   
   US1 = map(analogRead(pinUS1), 1023, 0, 0, 100);  //US1
   US2 = map(analogRead(pinUS2), 1023, 0, 0, 100);  //US2
   US3 = map(analogRead(pinUS3), 1023, 0, 0, 100);  //US3
   LUM = map(analogRead(pinLDR), 0, 1023, 0, 100);
   BAT = ((0.0095*analogRead(pinBAT))+0.2953);  //voltagem da bateria
       

   dados[0] = ("%02d", now.hour());
   dados[1] = ("%02d", now.minute());
   dados[2] = ("%02d", now.second());
   dados[3] = t1*100; //T1
   dados[4] = dht1.readHumidity();  //UR1
   dados[5] = t2*100;  //T2
   dados[6] = dht2.readHumidity();  //UR2
   dados[7] = VV*100;  //velocidade do vento
   dados[8] = PREC; 
   dados[9] = ts*100;  //TS1
   dados[10] = US1;
   dados[11] = US2;
   dados[12] = US3;
   dados[13] = LUM;
   dados[14] = (BAT*100);  //voltagem da bateria


     gravar_sd();
     mostra_lcd();
     
     for(i=0;i<3;i++){
        i=i+1;
        radio.write(dados, sizeof(dados));
        delay(4);
     }
     
        for(int i=0;i<18;i++){
          Serial.print(dados[i]); Serial.print("   |   ");
          delay(1);
        }
}




void mostra_lcd(){
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("T1:");
   display.print(float (dados[3])/100);
   display.setCursor(50,0);
   display.print("U1:");
   display.print(dados[4]);
   display.setCursor(0,10);
   display.print("BAT:");
   display.print(BAT);
   display.print("v");
   if(dados[14] < 670){
     display.print(" LOW");
   }
   
   //display.setCursor(0,10);
   //display.print("T2:");
   //display.print(float (dados[8])/100);
   //display.setCursor(50,10);
   //display.print("U2:");
   //display.print(dados[9]);
   display.setCursor(0,20);
   display.print("V:");
   display.print((dados[7])/100);
   display.setCursor(40,20);
   display.print("P:");
   display.print(float (dados[8])/100);
   display.setCursor(0,30);
   display.print("US: ");
   display.print(dados[10]);
   display.setCursor(45,30);
   display.print(dados[11]);
   display.setCursor(65,30);
   display.print(dados[12]);
   display.setCursor(35,40);
   display.print("TS:");
   display.print(float (dados[9])/100);

   display.setCursor(0,40);
   display.print("L:");
   display.print(dados[13]);
   display.display();
}

void mostra_serial(){

  for(i=0;i<18;i++){
    Serial.print(dados[i]); Serial.print('   |   ');
  }
  Serial.println();
}

void gravar_sd(){
   file.open("data.txt", FILE_WRITE);
   file.print(ano); file.print(('\t'));
   file.print(mes); file.print(('\t'));
   file.print(dia); file.print(('\t'));
   file.print(dados[0]); file.print(('\t'));
   file.print(dados[1]); file.print(('\t'));
   file.print(dados[2]); file.print(('\t'));
   file.print(t1); file.print(('\t'));
   file.print(dados[4]); file.print(('\t'));
   file.print(t2); file.print(('\t'));
   file.print(dados[6]); file.print(('\t'));
   file.print(VV); file.print(('\t'));
   file.print(PREC); file.print(('\t'));
   file.print(ts); file.print(('\t'));
   file.print(dados[10]); file.print(('\t'));
   file.print(dados[11]); file.print(('\t'));
   file.print(dados[12]); file.print(('\t'));
   file.print(dados[13]); file.print(('\t'));
   file.print(dados[14]); file.print(('\t'));

   file.println();
   file.close();
}

//------------------------------------------------------------  SETUP  --------------------------------------------------
void setup(void){
  Serial.begin(115200);
  display.begin();

  display.setContrast(40); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(23,0);  //Seta a posição do cursor
  display.println("ESTACAO");
  display.setCursor(4,10);
  display.print("METEOROLOGICA"); 
  display.display();
  pinMode(pinBL, OUTPUT);
  digitalWrite(pinBL, LOW);
  

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    display.print(" no rtc");
  while (1);
  }
  
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(50);
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  radio.setCRCLength(RF24_CRC_16);
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[0]);
    
  dht1.begin();
  dht2.begin();

    delay(1000);
   if (!sd.begin(SD_CHIP_SELECT_PIN)) {
      sd.initErrorHalt();
      Serial.println("initialization failed!");
      display.setTextSize(1);
      display.setCursor(0,20);
      display.println("SD error");
      display.display();
    return;
  }
  Serial.println("SD Pronto");
 // Serial.println("Ano;Mes;Dia;Hora;Min;Seg;T1;UR1;T2;UR2;VV;PREC;TS;US1;US2;US3;LUM;BAT");
  display.setCursor(0,20);
  display.println("SD Pronto");
  display.display();
  /*file.open("data.txt", FILE_WRITE);
  file.println();
  file.print("Ano;Mes;Dia;Hora;Min;Seg;T1;UR1;T2;UR2;VV;PREC;TS;US1;US2;US3;LUM;BAT");
  file.println();
  file.close();*/

  if (!sensors.getAddress(sensor1, 0)) {
     Serial.println("Sensor 1 nao encontrado !"); 
     display.setCursor(0,30);
     display.print("TSerro");  
  }

  
  
  pinMode(pinL, INPUT);
  pinMode(pinUS1, INPUT);
  pinMode(pinUS2, INPUT);
  pinMode(pinUS3, INPUT);
  pinMode(pinTS, INPUT);
  pinMode(pinLDR, INPUT);
  //pinMode(pinTS3, INPUT);
  pinMode(pinDHT1, INPUT);
  pinMode(pinDHT2, INPUT);
  pinMode(pinANE, INPUT);
  pinMode(pinPLUVI1, INPUT);
  pinMode(pinPLUVI2, INPUT);
  pinMode(pinBAT, INPUT);
  
  
  display.display();
  
  delay(1000);
  time0 = millis();
  timea0 = millis();
  armazena();
  delay(10000);
  digitalWrite(pinBL, HIGH);
  display.setContrast(0);
}

//--------------------------------------------------------------  LOOP  ----------------------------------------------------
void loop(void){

  time1 = millis();
  timea1 = millis();

//-------------------  PLUVIOMETRO  -----------------

  if(digitalRead(pinPLUVI1) == 0 and st == 0)
    st = 1;
  if(digitalRead(pinPLUVI2) == 0 and st == 0)
    st = 2;

//Serial.print(digitalRead(pinPLUVI1));Serial.print("      ");Serial.println(digitalRead(pinPLUVI2));

   if(digitalRead(pinPLUVI1) == 0 and st == 2){
    c1++;
    st = 1;
    }
  if(digitalRead(pinPLUVI2) == 0 and st == 1){
    c2++;
    st = 2;
    } 
   PREC = ((((vol1*c1)+(vol2*c2))/area)*100);

Serial.print(c1);Serial.print("      ");Serial.println(c2);


//---------------  VELOC VENTO  ---------------------

//Serial.print(digitalRead(pinANE));
    if(digitalRead(pinANE) == 0){
      cc++;
    }

    if(digitalRead(pinANE) > stV and cc > 30){
      V++;
      cc = 0;
      //Serial.println(V);
    }
    stV = digitalRead(pinANE);
     
  //Serial.print("   |   ");
   //Serial.println(V);


//--------------------  US BAT  ---------------------

//Serial.print(US1); Serial.print("   |   "); Serial.print(US2); Serial.print("   |   "); Serial.print(US3); Serial.print("   |   "); Serial.print(LUM); Serial.print("   |   "); Serial.println(BAT);



   if(digitalRead(pinL) == 1){
    digitalWrite(pinBL, LOW);
    display.setContrast(40);
    timea0 = millis();
   }

   if(timea1 - timea0 >= 20000){
    digitalWrite(pinBL, HIGH);
    display.setContrast(0);
   }
   
   
   
   //-----  gravar e enviar  --------
   if(time1 - time0 >= 60000){
    armazena();

   time0 = millis();
   }
   
 


}
  

#else  // SD_SPI_CONFIGURATION >= 3
#error SD_SPI_CONFIGURATION must be set to 3 in SdFat/SdFatConfig.h
#endif  //SD_SPI_CONFIGURATION >= 3

