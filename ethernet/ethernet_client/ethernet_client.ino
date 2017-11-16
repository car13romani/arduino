//inclusão de bibliotecas
#include <SPI.h> //inclusão da biblioteca SPI
#include <Ethernet.h> //inclusão da biblioteca Ethernet
#include "DHT.h" //inclusão da biblioteca para o DHT
 
//definições para o sensor DHT
#define DHTPIN 2     // define a porta que o DHT está conectado
#define DHTTYPE DHT22   // define o sensor como DHT22
DHT dht(DHTPIN, DHTTYPE); //chama a função do dht passando porta e tipo de sensor
 
// Configurações para Ethernet
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; // Endereço MAC precisa ser único na rede
IPAddress ip(192,168,1,106); // Endereço IP, altere para sua rede
EthernetClient client;
 
// Configurações do Servidor ThingSpeak
char thingSpeakAddress[] = "monitoracerrado.net.br"; // endereço IP
String writeAPIKey = "sua chave de escrita aqui"; // chave de escrita
const int updateThingSpeakInterval = 30 * 1000; // Intervalo para atualização
char thingspeak_data[128]; //variável que guarda os dados que serão enviados
 
//variavéis para controle
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;
 
//######################################################################################
void setup()
{
  // Inicia saída serial para debugar via Serial Monitor
  Serial.begin(9600);
  Serial.println("DHTxx teste!"); // Mensagem antes de inicializar sensor DHT
  dht.begin();//inicia sensor DHT
  Ethernet.begin(mac,ip);//inicializa placa Ethernet
 
}
//#######################################################################################
void loop()
{
 
  char dht_temp[6];//cria variavel do tipo char que vai armazenar valores de temperatura do dht
  char dht_umid[6];//cria variavel do tipo char que vai armazenar valores de umidade do dht
  float h = dht.readHumidity();//faz leitura de umidade e armazena na variavel h do tipo float
  float t = dht.readTemperature();//faz leitura de temperatura e armazena na variavel t do tipo float
 
  if (isnan(t) || isnan(h)) {//verifica se existiu leitura de temperatura e umidade
    //Serial.println("Falha ao ler sensor DHT");//exibe mensagem em caso de erro na leitura
  } else {
    dtostrf(h,1,2,dht_umid);//copiando float umidade para char dht_umid
    dtostrf(t,1,2,dht_temp);//copiando float temperatura para char dht_temp
  }
   //salva na variavel char thingspeak_data variaveis que serão enviadas para o servidor thingspeak no formato field1=xx(valor umidade)&amp;field2=xx(valor temperatura)
   sprintf(thingspeak_data,"field1=%s&amp;field2=%s",dht_umid,dht_temp);  
 
  //verifica via http se a url de acesso ao servidor do thingspeak está disponível
  if (client.available())
  {
    char c = client.read();// se sim, lê resposta http
    //Serial.print(c); // e exibe via serial resposta completa, descomente para visualizar
  }
 
  // desconecta do servidor thingspeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...desconectado");
    Serial.println();
 
    client.stop();
  }
 
  // Faz Update de dados no ThingSpeak
  if(!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval))
  {
    updateThingSpeak(thingspeak_data); // envia variavel thingspeak_data para a função updateThingSpeak
    Serial.print("Dados enviados:");
    Serial.println(thingspeak_data);// exibe via serial os dados enviados de temperatura e umidade
  }
  updateThingSpeak(thingspeak_data); 
  // Verifica se o módulo/Shield Ethernet precisa ser reiniciado
  if (failedCounter > 3 ) {startEthernet();}//se o contador de falhas for &gt; 3 , inicia novamente a placa Ethernet
 
  lastConnected = client.connected();//armazena em lastConnected o horário da última conexão
}
//#######################################################################################
void updateThingSpeak(String tsData)//funçao recebe a variavel char contendo os campos com respectivos dados a serem enviados ao servidor thingspeak
{
  if (client.connect(thingSpeakAddress, 80))//tenta conexão com o servidor thingSpeakAdrress,porta do servidor
  {
    //cabeçalho de POST via HTTP
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: monitoracerrado.net.br\n");//ip do servidor
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");//chave de escrita necessária do canal
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());//comprimento dos dados a serem enviados
    client.print("\n\n");
    client.print(tsData);//propriamente os dados field1 &amp; field que serão enviados
 
    lastConnectionTime = millis();
 
    if (client.connected())
    {
      Serial.println("Conectando ao Monitora Cerrado...");
      Serial.println();
 
      failedCounter = 0;
    }
    else
    {
      failedCounter++;
 
      Serial.println("Conexão ao Monitora Cerrado falhou ("+String(failedCounter, DEC)+")");
      Serial.println();
    }
 
  }
  else
  {
    failedCounter++;
 
    Serial.println("Conexão ao Monitora Cerrado falhou ("+String(failedCounter, DEC)+")");
    Serial.println();
 
   lastConnectionTime = millis();
  }
}
 
void startEthernet()
{
  client.stop();
  Serial.println("Connectando Arduino à rede...");
  Serial.println();
  delay(1000);
  Ethernet.begin(mac,ip);//inicializa placa Ethernet
  delay(1000);
}
