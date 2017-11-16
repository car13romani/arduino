const int buzzer = 10;
int i = 2000;
int j = 80;
int k = 50;

/*Criamos uma constante que armazena o número da porta*/
 
 
void setup() {
/*metodo setup só é executado uma unica vez*/
pinMode(buzzer,OUTPUT); 
}
void loop() { 

tone(buzzer,i);  
delay(j);
noTone(buzzer);
delay(k);

tone(buzzer,i);  
delay(j);
noTone(buzzer);
delay(k);

tone(buzzer,i);  
delay(j);
noTone(buzzer);
delay(k);

tone(buzzer,i);  
delay(j);
noTone(buzzer);
delay(k);

delay(700);
}
