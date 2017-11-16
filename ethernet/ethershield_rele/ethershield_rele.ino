/*Mude o mac[] para o mac da sua placa Ethernet Shield (números localizados embaixo da placa) e o IP de acordo com sua rede local. Por exemplo, se o seu roteador 
tiver o IP 192.168.1.1. Digite um IP 192.168.1.xxx. Sendo xxx de sua escolha. Cuidado para não colocar um IP igual de um PC de sua rede local. Aqui foi escolhido o final 177. 

Cuidado também com a alimentação do Arduino. Utilize conectado ao USB do PC ou a uma fonte externa de 0 a 12V com 1A de corrente.*/

#include <SPI.h>
#include <Ethernet.h>
boolean incoming = 0;
int rele1 = 0;
int rele2 = 0;
int loopporta = 1;

byte mac[] = { 0x00, 0xAB, 0x00, 0x00, 0x00, 0x01 };
IPAddress ip(192,168,0,200);

EthernetServer server(80);
void setup()
{

Ethernet.begin(mac, ip);
server.begin();
Serial.begin(9600);

pinMode(8, OUTPUT);
digitalWrite(8, LOW);
pinMode(7, OUTPUT);
digitalWrite(7, LOW);
}

void loop()
{
  
  
  
// listen for incoming clients
EthernetClient client = server.available();
if (client) {
// an http request ends with a blank line
boolean currentLineIsBlank = true;
String str;
while (client.connected()) {
if (client.available()) {
char c = client.read();
str.concat(c);
if(str.endsWith("/1on")) rele1 =1;
else if(str.endsWith("/1off")) rele1 =0;
if(str.endsWith("/2on")) rele2 =1;
else if(str.endsWith("/2off")) rele2 =0;
if (c == '\n' && currentLineIsBlank) {
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println();
if(rele1 == 1)
{
client.println("ligado1" );
digitalWrite(7, HIGH);
}
else if (rele1 ==0)
{
client.println("desligado1" );
digitalWrite(7, LOW);
}
if(rele2 == 1)
{
  client.println("#########     PORTA ABERTA     ##########");


  while(loopporta != 10)    //    loop para abrir a porta
  {
    loopporta++; 
    digitalWrite(8, HIGH);
    delay(50);
    digitalWrite(8, LOW);
    delay(50);    
    
  }
}

break;
}
if (c == '\n') {
currentLineIsBlank = true;
}
else if (c != '\r') {
currentLineIsBlank = false;
}
}
}
// give the web browser time to receive the data
delay(1);
// close the connection:
//client.stop();
}

digitalWrite(8, LOW);
  digitalWrite(7, LOW);
}
