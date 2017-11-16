#include <SPI.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//Armazena os dados recebidos
int dados[20];

Adafruit_PCD8544 display = Adafruit_PCD8544(6, 5, 4, 3, 2);

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


void setup()
{
  Serial.begin(115200);
  display.begin();
  display.setContrast(50); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(23,0);  //Seta a posição do cursor
  display.println("ESTACAO");
  display.setCursor(4,10);
  display.print("METEOROLOGICA"); 
  display.display();
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(50);
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  radio.setCRCLength(RF24_CRC_16);
  radio.setRetries(15,15);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(2000);
  Serial.println("Aguardando dados...");

}

void loop(){
    if (radio.available()){
      bool done = false;
    while (!done){
         done = radio.read( dados, sizeof(dados));
    }

        for(int i=0;i<20;i++){
          Serial.print(dados[i]); Serial.print("\t");
          delay(1);
        }
         Serial.println();    
         
         display.clearDisplay();   //Apaga o buffer e o display
         display.setCursor(0,0);
         display.print("T1:");
         display.print(float (dados[3])/100);
         display.setCursor(50,0);
         display.print("U1:");
         display.print(dados[4]);
         display.setCursor(0,10);
         display.print("BAT:");
         display.print(float (dados[14])/100);
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
         display.print(float (dados[7])/100);
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
}
  

