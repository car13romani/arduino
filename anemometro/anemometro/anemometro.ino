#define pinANE 3
int cc = 0; int V = 0; int stV = 0; float VV = 0.00;
long int time0 = 0;
long int time1 = 0;

void setup(){

  Serial.begin(9600);
  pinMode(pinANE, INPUT);
  time0 = millis();
}

void loop(){
  time1 = millis();
if(digitalRead(pinANE) == 0){
      cc++;
    }

    if(digitalRead(pinANE) > stV and cc > 30){
      V++;
      cc = 0;
      //Serial.println(V);
    }
    stV = digitalRead(pinANE);
    //Serial.println(V);
  if(time1 - time0 >= 10000){
    VV = (V*0.395839)/10;
    V=0;
    Serial.print("     |     "); Serial.println(VV);

   time0 = millis();
   }




}
