//Programa : Teste NRF24L01 - Emissor - Botoes
//Autor : Adilson Thomsen

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Armazena os dados enviados
int dados[10];
int s = 1;
//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//Define os pinos dos botoes
int pino_botao1 = 7;
int pino_botao2 = 2;

void setup()
{
  //Define os botoes como entrada e
  //ativa pull-up
  pinMode(7, INPUT);
  digitalWrite(7,HIGH);
  pinMode(2, INPUT);
  digitalWrite(2,HIGH);

  //Inicializa a serial
  Serial.begin(57600);
  Serial.println("Pressione botao 1 ou 2 para iniciar a comunicacao...");
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de transmissao
  radio.openWritingPipe(pipe);
  
}

void loop()
{
  //Envia o numero 1 caso o botao1 seja pressionado
 // if (digitalRead(pino_botao1) == LOW)
 // {

    
    Serial.println("Botao 1 pressionado !");
    dados[0] = s+10;
    dados[1] = s+20;
    dados[2] = s+30;
    dados[3] = s+13;
    radio.write(dados, sizeof(dados));
    s++;
 // }
  
  //Envia o numero 2 caso o botao2 seja pressionado
  if (digitalRead(pino_botao2) == LOW)
  {
    Serial.println("Botao 2 pressionado !");
    dados[0] = 12345;
    radio.write(dados, 50);
  }
  delay(2);
}
