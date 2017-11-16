#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
// Definicoes pino modulo RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 

// Leds indicadores acesso liberado ou negado
int led_liberado = 4;
int led_fechado = 3;
int Pin = 6;

char st[20];

//============================================================
void setup() 
{
  pinMode(led_liberado, OUTPUT);
  pinMode(led_fechado, OUTPUT);
  pinMode(Pin, OUTPUT);
  digitalWrite(Pin, HIGH);
  Serial.begin(9600);
  // Inicia  SPI bus
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init(); 
  // Mensagens iniciais no serial monitor
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  digitalWrite(led_fechado, HIGH);
}

//=========================================================
void abrir()
{
    digitalWrite(led_fechado, LOW);
    digitalWrite(led_liberado, HIGH);
    Serial.println("Acesso liberado !");
    Serial.println();
  
    for (int i=0; i<=10; i++){
        digitalWrite(Pin, LOW);
        delay(30);
        digitalWrite(Pin, HIGH);
        delay(30);
    }
    delay(2000);
    digitalWrite(led_liberado, LOW);
    digitalWrite(led_fechado, HIGH);
}
//==========================================================

void loop() 
{
  // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  Serial.print(conteudo.substring(1));
  
  // Testa se o cartao1 foi lido
  if (conteudo.substring(1) == "B2 AD D5 E5")
  {
    abrir();
    }

  delay(500);
}
