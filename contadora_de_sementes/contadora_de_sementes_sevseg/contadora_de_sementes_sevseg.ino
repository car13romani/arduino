

float valor = 0.0;  //Variável que receberá o valor do LDR
int led_pin = 3; // Pino do LED
int analogin = A6; // Pino em será ligado o LDR 
int n = 0;
int x = 0;
int anterior = 220; //Valor mínimo antes de começar a aumentar
int inicio_grao = 0; //Valor máximo antes de começar a diminuir
int media = 0;
int soma = 0;
float tempo =0;
float tempo2 =0;
float media_tempo = 0;
int gatilho =0;




void setup(){
  
  
  Serial.begin(9600); 
  pinMode(led_pin, OUTPUT); 
  delay(100);
  for(int i = 0; i < 10000; i++){
    valor = analogRead(analogin);
    //Serial.println(valor);
    soma = soma + valor;
  }
  media = soma / 10000;
  Serial.println("\n\n\n");
  Serial.println(media);
  Serial.println("OK!"); // Valor será mostrado no Serial Monitor
  Serial.println("\n\n\n");
  anterior = media;
}

void loop(){
  valor = analogRead(analogin); // A variável valor recebe o valor do LDR
//  Serial.println(valor); // Valor será mostrado no Serial Monitor
  //delay(1); // Faz uma pausa de 250 milissegundos
  if (valor < (anterior - 8)){ //Começou a contar o primeiro grao
    inicio_grao = 1;
//    Serial.println("1 - valor: ");
//    Serial.println(valor);
//    Serial.println("1 - anterior: ");
//    Serial.println(anterior);
    anterior = valor;
  }else if(valor > (anterior + 8)){
    if(inicio_grao == 1){
      n++;
      inicio_grao = 0;
      Serial.println(n);// Valor será mostrado no Serial Monitor   
      
    }
//    Serial.println("2 - valor: ");
//    Serial.println(valor);
//    Serial.println("2 - anterior: ");
//    Serial.println(anterior);
    anterior = valor;
  }
  anterior = valor;

// Teste de contagem por segundo 
  if (n==1){
      tempo = millis();      
    }
    if ((gatilho == n) && ((millis() - tempo2)>=10000) && (x == 0)){
      Serial.println("Gatilho: ");
      Serial.println(gatilho);
      Serial.println("N: ");
      Serial.println(n);
      Serial.println("Tempo: ");
      Serial.println(tempo);
      Serial.println("Tempo2: ");
      Serial.println(tempo2);
      Serial.println("Millis: ");
      Serial.println(millis());

      media_tempo=n/ ( ( (tempo2 - tempo) )  / 1000);
      Serial.println(media_tempo);
      

      
      x = 1;
    }else if (gatilho != n){
      tempo2 = millis();
      gatilho = n;
    }
   
}
