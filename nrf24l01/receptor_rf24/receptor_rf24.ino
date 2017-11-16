//Programa : Teste NRF24L01 - Receptor - Led
//Autor : Adilson Thomsen

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Armazena os dados recebidos
int recebidos[15];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos

const uint64_t pipe = 0xE13CBAF433LL;

//Define os pinos dos leds
int LED1 = 5;
int LED2 = 3;
void setup()
{
  //Define os pinos dos leds como saida
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //Inicializa a serial
  Serial.begin(115200);
    while (!Serial) {
  ; // aguarde a serial conectar. Somente necessário para o Leonardo
  }
  
  //Inicializa a comunicacao
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(8);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openReadingPipe(1,pipe);      // Open a reading pipe on address 0, pipe 1
  radio.startListening();                 // Start listening
  radio.powerUp();
  radio.printDetails(); 

    delay(2000);
  Serial.println("Aguardando dados...");

}

void loop()
{
  //Verifica se ha sinal de radio
  if (radio.available())
  {
    bool done = false;    
    while (!done)
    {
      done = radio.read(recebidos, sizeof(recebidos));
      Serial.print("  st  "); Serial.print(recebidos[0]);
      Serial.print("     b1  "); Serial.print(recebidos[1]);
      Serial.print("     b2  "); Serial.print(recebidos[2]);
      Serial.print("     scu  "); Serial.print(recebidos[3]);
      Serial.print("     scd  "); Serial.print(recebidos[4]);
      Serial.print("     set  "); Serial.print(recebidos[5]);
      Serial.print("     act  "); Serial.print(recebidos[6]);
      Serial.print("     ax  "); Serial.print(recebidos[7]);
      Serial.print("     ay  "); Serial.print(recebidos[8]);
      Serial.print("     az  "); Serial.print(recebidos[9]);
      Serial.print("     gx  "); Serial.print(recebidos[10]);
      Serial.print("     gy  "); Serial.print(recebidos[11]);
      Serial.print("     gz  "); Serial.println(recebidos[12]);
      delay(10);
    }
  }
  else
  {
 Serial.println("Aguardando dados...");
  }
}
