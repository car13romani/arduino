#include<Wire.h>

int pin1 = 8;
int pin2 = 10;
int pin3 = 12;

int tolM = 100;
int tolm = -tolM;


const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY;
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);

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

  if(AcY < tolM){
    digitalWrite(pin3, LOW);
  }
  else{
    digitalWrite(pin3, HIGH);
  }

    if(AcY > tolm){
    digitalWrite(pin2, LOW);
  }
  else{
    digitalWrite(pin2, HIGH);
  }

    if(AcX < tolM && AcX > tolm){
    digitalWrite(pin1, LOW);
  }
  else{
    digitalWrite(pin1, HIGH);
  }


  

  //Envia valor X do acelerometro para a serial e o LCD
  Serial.print("AcX = "); Serial.print(AcX);
   
  //Envia valor Y do acelerometro para a serial e o LCD
  Serial.print(" | AcY = "); Serial.println(AcY);

  delay(100);
}



