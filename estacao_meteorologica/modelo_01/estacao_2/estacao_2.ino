#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "DHT.h"
 
#define DHTPIN 8 // pino que estamos conectado
#define DHTTYPE DHT22 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int soloPin = A1;
int batPin = A2;

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
int dados[4];
int i = 0;
int j = 0;
int umsolo = 0; int us1 = 0; int us2 = 0; int us3 = 0; int us4 = 0;
void setup(void)
{
  dht.begin();
  Serial.begin(57600);
  pinMode(soloPin, INPUT);
  pinMode(batPin, INPUT);
  
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(100);
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  radio.setCRCLength(RF24_CRC_16);

  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]);
  //radio.printDetails();
}

void loop()
{
  while(i<5){
    
    i=i+1;

    radio.write(dados, sizeof(dados));
  }
  i=0;
  delay(2500);
  
  while(j<5){
    j=j+1;
    umsolo = analogRead(soloPin);
    us4 = us3;
    us3 = us2;
    us2 = us1;
    us1 = umsolo;
    delay(100);
  }
  j=0;
  dados[0] = dht.readTemperature();
  dados[1] = dht.readHumidity();
  dados[2] = (us1+us2+us3+us4)/4;
  dados[3] = analogRead(batPin);
  Serial.print(dados[0]); Serial.print("   ");
  Serial.print(dados[1]); Serial.print("   ");
  Serial.print(dados[2]); Serial.print("   ");
  Serial.print(dados[3]); Serial.println("   ");
}

