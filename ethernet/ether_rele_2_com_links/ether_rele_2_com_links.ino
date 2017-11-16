#include <SPI.h>
#include <Ethernet.h>
  
byte mac[] = { 0x00, 0xAB, 0x00, 0x00, 0x00, 0x01 };
byte ip[] = {10, 6, 5, 231};
byte myDns[] = {10, 6, 0, 3};
byte myGtW[] = {10, 6, 4, 1};
byte subnet[] = {255, 255, 254, 0};
     
EthernetServer server(80);
  
String readString;
int Pin = 7;
EthernetClient porta;
char server_porta[] = "200.132.140.21"; 

void setup(){
  Serial.begin(9600);
  pinMode(4,OUTPUT); //desabilita SD do ethernet shield se não funcionar com o 4 tentar com o 10
  digitalWrite(4,HIGH); // desabilita SD do ethernet shield se não funcionar com o 4 tentar com o 10
  pinMode(Pin, OUTPUT);
  Ethernet.begin(mac, ip, myDns, myGtW, subnet);
  server.begin();
  digitalWrite(Pin, HIGH);
  
  Serial.println("Pausa para inicializar a rede: 30s");
  delay(30000);
  
  if (porta.connect(server_porta, 80)) {
    Serial.println("connected");
  }else {
    Serial.println("FAIL");
  }
}

void loop(){
  EthernetClient client = server.available();

  if (client) {
    while (client.connected()) {
       // delay(10000);
      //client.println("GET http://200.132.140.21/LabSIM/index.php?link=teste");
      if (client.available()) { 
        char c = client.read(); // c é a variavel que recebe algum valor do cliente
  
        if (readString.length() < 100) {
          readString += c;              
        }
 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          /*l 
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Porta Inteligente</H1>");
          client.println("<hr />");
          client.println("<br />");
          
          client.println("<button name='botao'  type='submit'><a href=\"/abrirporta\"\">Abrir Porta</a><a href=\"\"></a></button>");
         
          //client.println("<input type='button' name='botao-ok' value='Abrir porta' submit='<a href=\"/?abrirporta\">'");
          //client.println("<a href=\"/?abrirporta\"\">Abrir Porta</a>");
          //client.println("<a href=\"/?ledoff\"\">Desligar o led</a><br />");    
       
          client.println("</BODY>");
          client.println("</HTML>");
          */
          delay(1);
          client.stop();
          
          if(readString.indexOf("abrirporta") > 0)
          {
            for (int i=0; i<=20; i++){
            digitalWrite(Pin, LOW);
            delay(30);
            digitalWrite(Pin, HIGH);
            delay(30);
            }
          }
          else {
            if(readString.indexOf("?ledoff") > 0)
            {
              digitalWrite(Pin, HIGH);
            }
            
          }
          readString="";     
        }
      }
    }
  }
  else{
//    Serial.println("else");
//    delay(15000);
//    porta.println("GET /LabSIM/index.php?link=teste");
//    porta.println("Host: 200.132.140.21");
//    Serial.println("Enviando comando");
  }

}

