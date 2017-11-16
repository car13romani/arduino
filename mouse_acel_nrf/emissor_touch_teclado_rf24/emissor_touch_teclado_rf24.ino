//Programa : Teste NRF24L01 - Emissor - Botoes
//Autor : Adilson Thomsen

#include <SPI.h>
//#include "nRF24L01.h"
#include "RF24.h"
#include <Wire.h>

//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

//Armazena os dados enviados
int dados[12];
int s = 1;

//botoes
const int st = A0;
const int b1 = 3;
const int b2 = 4;
const int sc = A1;
const int botoes = A2;  //up down left right
int bot;


//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

void setup()
{
  
  pinMode(st,INPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(sc,INPUT);
  pinMode(botoes,INPUT);

  
  //Inicializa a serial
  Serial.begin(115200);
 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
  
  //Inicializa a comunicacao

  radio.begin();
  delay(100);
  //Entra em modo de transmissao
  radio.openWritingPipe(pipe);       

  delay(100);
  
}

void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    int ax = AcX/10;
    int ay = AcY/10;
    int az = AcZ/10;
    int gx = GyX/100;
    int gy = GyY/100;
    int gz = GyZ/100;

   int setas = analogRead(botoes);
   if(setas < 5) {bot = 1;}
      else if(setas > 1000) {bot = 2;}
      else if(setas < 905 and setas > 890) {bot = 3;}
      else if(setas < 845 and setas > 835) {bot = 4;}
      else if(setas < 965 and setas > 955) {bot = 5;}
      else if(setas < 790 and setas > 780) {bot = 6;}
      else if(setas < 680 and setas > 670) {bot = 7;}
      else if(setas < 740 and setas > 720) {bot = 8;}
      else {bot = 0;}




    dados[0] = analogRead(st);
    dados[1] = digitalRead(b1);
    dados[2] = digitalRead(b2);
    dados[3] = analogRead(sc);
    dados[4] = bot;
    dados[5] = ax;
    dados[6] = ay;
    dados[7] = az;
    dados[8] = gx;
    dados[9] = gy;
    dados[10] = gz;
    radio.write(dados, sizeof(dados));
    
   Serial.println("enviando...");

}
