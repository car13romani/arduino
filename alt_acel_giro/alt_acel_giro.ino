    #include "Wire.h"
    #include "Adafruit_BMP085.h"

    
    Adafruit_BMP085 bmp;
    const int MPU=0x68;  
    int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
    
  void setup() {
    Serial.begin(115200);
    bmp.begin();
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B); 
     
    //Inicializa o MPU-6050
    Wire.write(0); 
    Wire.endTransmission(true);
  }

    
  void loop() {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    //Solicita os dados do sensor
    Wire.requestFrom(MPU,14,true);  

    AcX=Wire.read()<<8|Wire.read();  
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
    Tmp=Wire.read()<<8|Wire.read();
    GyX=Wire.read()<<8|Wire.read();
    GyY=Wire.read()<<8|Wire.read();
    GyZ=Wire.read()<<8|Wire.read();

      
   Serial.print(bmp.readAltitude(101500)); Serial.print(" | ");
   Serial.print(AcX); Serial.print(" | "); Serial.print(AcY); Serial.print(" | "); Serial.print(AcZ); Serial.print(" | ");
   Serial.print(GyX); Serial.print(" | "); Serial.print(GyY); Serial.print(" | "); Serial.print(GyZ); Serial.println(" | ");
   


   
   delay(1);
   }


