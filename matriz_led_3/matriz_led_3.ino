#include <SPI.h>

// Programa : Painel de leds com modulo Max7219  
// Adaptacoes e comentarios : Arduino e Cia  

// Carrega a biblioteca MD_MAX72xx  
#include <MD_MAX72xx.h>  
#include "DHT.h"
#include <Wire.h>
#include "RTClib.h"

#define DHTPIN A0 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11
  
// Numero de modulos utilizados  
#define     MAX_DEVICES     8  
#define     MAX_DEVICES1     8
  
// Ligacoes ao Arduino  
#define     DATA_PIN     2  
#define     CS_PIN       8 
#define     CLK_PIN      3 
#define     DATA_PIN1     5  
#define     CS_PIN1       6 
#define     CLK_PIN1      7 
   
MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx1 = MD_MAX72XX(DATA_PIN1, CLK_PIN1, CS_PIN1, MAX_DEVICES1);  
DHT dht(DHTPIN, DHTTYPE);
// Velocidade do scroll  
#define SCROLL_DELAY     150  
#define SCROLL_DELAY1    200  
// Colunas entre cada caracter  
#define     CHAR_SPACING     1  
  
#define     BUF_SIZE     100  
char curMessage[BUF_SIZE];  
char newMessage[BUF_SIZE];  
#define     BUF_SIZE1     100  
char curMessage1[BUF_SIZE1];  
char newMessage1[BUF_SIZE1];
RTC_DS3231 rtc;
long int anterior = 1000;

int scrollDelay;  
// ################################   linha 1  
uint8_t scrollDataSource(uint8_t dev, MD_MAX72XX::transformType_t t)  
{  
  static char          *p = curMessage;  
  static uint8_t     state = 0;  
  static uint8_t     curLen, showLen;  
  static uint8_t     cBuf[8];  
  uint8_t colData;  

  switch(state)  
  {  
  case 0:  
    showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);  
    curLen = 0;  
    state++;  
    if (*p == '\0')  
    {  
      p = curMessage;  
    }  
  case 1:       
    colData = cBuf[curLen++];  
    if (curLen == showLen)  
    {  
      showLen = CHAR_SPACING;  
      curLen = 0;  
      state = 2;  
    }  
    break;  
  case 2:  
    colData = 0;  
    curLen++;  
    if (curLen == showLen)  
      state = 0;  
    break;  
    default:  
      state = 0;  
  }  
  return(colData);  
}  

//################################### linha 2

uint8_t scrollDataSource1(uint8_t dev, MD_MAX72XX::transformType_t t)  
{  
  static char          *q = curMessage1;  
  static uint8_t     state1 = 0;  
  static uint8_t     curLen1, showLen1;  
  static uint8_t     cBuf1[8];  
  uint8_t colData1;  

  switch(state1)  
  {  
  case 0:  
    showLen1 = mx1.getChar(*q++, sizeof(cBuf1)/sizeof(cBuf1[0]), cBuf1);  
    curLen1 = 0;  
    state1++;  
    if (*q == '\0')  
    {  
     q = curMessage1;  
    }  
  case 1:       
    colData1 = cBuf1[curLen1++];  
    if (curLen1 == showLen1)  
    {  
     showLen1 = CHAR_SPACING;  
     curLen1 = 0;  
     state1 = 2;  
    }  
    break;  
  case 2:  
    colData1 = 0;  
    curLen1++;  
    if (curLen1 == showLen1)  
     state1 = 0;  
    break;  
    default:  
    state1 = 0;  
  }  
  return(colData1);  
}  
  
void scrollText(void)  
{  
  static uint32_t     prevTime = 0;  
  if (millis()-prevTime >= SCROLL_DELAY)  
  {  
    mx.transform(MD_MAX72XX::TSR);       
    //prevTime = millis();  
    //mx1.transform(MD_MAX72XX::TSR);       
    prevTime = millis();
  }  
}  

void scrollText1(void)  
{  
  static uint32_t     prevTime1 = 0;  
  if (millis()-prevTime1 >= SCROLL_DELAY1)  
  {  
    mx1.transform(MD_MAX72XX::TSR);       
    prevTime1 = millis();
  }  
}  
  
void setup()  
{


  if (! rtc.begin()) {
    while (1);
  }
  //if (rtc.lostPower()) {
    //Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2016, 9, 29, 18, 50, 0));
 // }
  
  Serial.begin(57600);  
  mx.begin();  
  mx1.begin();  
  mx.setShiftDataInCallback(scrollDataSource);  
  mx1.setShiftDataInCallback(scrollDataSource1); 
  // Define o nivel de luminosidade  
  mx.control(MD_MAX72XX::INTENSITY, 4);  
  mx1.control(MD_MAX72XX::INTENSITY, 4);  
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx1.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  // Mensagem a ser exibida  

 String str1 = " LabSIM - Laboratorio de Sistemas Inteligentes e Modelagem  -  43";
 str1 = str1 + (char)166;
 str1 = str1 + " Expofeira - Itaqui          ";

   

  dht.begin();
  rtc.begin();
  delay(1000);

  int t = dht.readTemperature();
  String str = "Temperatura: ";
  str = str + t;
  str = str + (char)34;
  str = str + "C";
  str = str + "    ";
  DateTime now = rtc.now();
  str = str + "Hora: ";
  char buf[2];
  sprintf(buf, "%02d", now.hour());
  str = str + buf;
  str = str + ":";
  sprintf(buf, "%02d", now.minute());
  str = str + buf;
  str = str + "     ";
  strcpy(curMessage1, str.c_str());  
  newMessage1[0] = '\0';

  strcpy(curMessage, str1.c_str());  
  newMessage[0] = '\0';
  
  anterior = millis();
}  
   
void loop()   
{

  
  if(millis() - anterior > 30000){
    int t = dht.readTemperature();
    String str = "Temperatura: ";
    str = str + t;
    str = str + (char)34;
    str = str + "C";
    str = str + "    ";
    DateTime now = rtc.now();
    str = str + "Hora: ";
    char buf[2];
    sprintf(buf, "%02d", now.hour());
    str = str + buf;
    str = str + ":";
    sprintf(buf, "%02d", now.minute());
    str = str + buf;
    str = str + "     ";
    mx.control(0, MAX_DEVICES-1, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx1.control(0, MAX_DEVICES-1, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    delay(10);
    
    String str1 = " LabSIM - Laboratorio de Sistemas Inteligentes e Modelagem  -  43";
    str1 = str1 + (char)166;
    str1 = str1 + " Expofeira - Itaqui          ";
    strcpy(curMessage1, str.c_str());  
    newMessage1[0] = '\0';
    strcpy(curMessage, str1.c_str());  
    newMessage[0] = '\0';
    
    
    delay(10);
    mx.control(0, MAX_DEVICES-1, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    mx1.control(0, MAX_DEVICES-1, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    anterior = millis();
  }
  scrollText();
  scrollText1(); 
} 
