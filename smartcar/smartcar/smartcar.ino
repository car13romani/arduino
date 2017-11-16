
#include <Ultrasonic.h>

//#include <Ultrasonic.h>
#include <IRremote.h>  
#include <Servo.h>
Ultrasonic ultrasonic(4,3);
//***********************define motor pin*************************
int MotorRight2=11;
int MotorRight1=10;
int MotorLeft2=8;
int MotorLeft1=9;
int counter=0;
int delay_servo = 300;
const int irReceiverPin = 2; //Infrared recive connect to pin 2

//***********************set detect IRcode*************************
long IRfront= 0xB54A02FD;        //go forward code
long IRback=0xB54A827D;         //go back code
long IRturnright=0xB54AC23D;    //turn right code
long IRturnleft= 0xB54A42BD;     //turn left code
long IRstop=0xF50A34CB;         //stop code
long IRcny70=0xB54A58A7;        //CNY70 automatic move mode
long IRAutorun=0xB54A1AE5;      //ultrasonic detect automatic move mode
long IRturnsmallleft= 0xF50AE619; 
//*************************dedine CNY70 pin************************************
const int SensorLeft = 19;      //left sensor input
const int SensorMiddle= 18 ;    //middle sensor input 
const int SensorRight = 17;     //right sensor input
int SL;    //left sensor status
int SM;    //middle sensor stattus
int SR;    //right sensor status
IRrecv irrecv(irReceiverPin);  // define IRrecv signal 
decode_results results;       // put decode result in "results" 
//*************************define ultrasonic module pin*****************************
int echoPin =3; // define ultrasonic module recive signal RX pin
int trigPin =4; // define ultrasonic module echo signal TX pin
int Fspeedd = 0; // distance in front
int Rspeedd = 0; // distance in right 
int Lspeedd = 0; // distance in left
int directionn = 0; // forward=8; back=2; left=4; right=6 
Servo myservo; // set myservo
int delay_time = 250; // stabilization time of servo motor turn back 
int Fgo = 8; // go forward
int Rgo = 6; // turn right 
int Lgo = 4; // turn left
int Bgo = 2; // go back
//********************************************************************(SETUP)
void setup()
{  
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // pin 8 (PWM)
  pinMode(MotorRight2, OUTPUT);  // pin 9 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // pin 10 (PWM) 
  pinMode(MotorLeft2,  OUTPUT);  // pin 11 (PWM)
  irrecv.enableIRIn();     // start infrared encode
  Serial.println("esperando comando");
   pinMode(SensorLeft, INPUT); //define left sensor 
  pinMode(SensorMiddle, INPUT);//define middle sensor 
  pinMode(SensorRight, INPUT); //define right sensor 
  //digitalWrite(2,HIGH);
  pinMode(echoPin, INPUT); // define ultrasonic recive pin
  pinMode(trigPin, OUTPUT); // define ultrasonic echo pin 
  myservo.attach(6); // deine servo motor pin

  Serial.println("pronto");
}
//******************************************************************(Void)
void advance(int a) // go forward
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  delay(a * 100); 
}
void right(int b) //turn right (single wheel)
{
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,LOW);
  delay(b * 100);
}
void left(int c) //turn left(single wheel) 
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,LOW);
  delay(c * 100);
}
void turnR(int d) //turn right (double wheels)
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,HIGH);
  delay(d * 100);
}
void turnL(int e) //turn left (double wheels)
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,HIGH);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);
  delay(e * 100);
} 
void stopp(int f) //stop
{
  digitalWrite(MotorRight1,LOW);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,LOW);
  digitalWrite(MotorLeft2,LOW);
  delay(f * 100);
}
void back(int g) //go back
{
  digitalWrite(MotorRight1,HIGH);
  digitalWrite(MotorRight2,LOW);
  digitalWrite(MotorLeft1,HIGH);
  digitalWrite(MotorLeft2,LOW);;
  delay(g * 100); 
}

void detection() //measure distance of three angle 
{ 
  detection(0);
}
void detection(int mode) //measure distance of three angle 
{ 
  int delay_time = 250; // stabilization time of servo motor turn back 
  //IF MODE = 0, normal process. IF MODE = 1, returned and look again.
  
  if(mode == 0){
    ask_pin_F(); // measure distance in front
    if(Fspeedd < 10) // if distance less then 5cm in front 
    {
      stopp(1); // clear output 
      back(10); // go back 0.2s
    }
    if(Fspeedd < 25) // if distance less then 15cm in front 
    {
      stopp(1); // clear output
      ask_pin_L(); // read distance in right
      delay(delay_time); // wait servo motor stability
      ask_pin_R(); // read distance in right  
      delay(delay_time); // wait servo motor stability

      delay(delay_servo);
  
      if(Lspeedd > Rspeedd) //if left distance larger than right 
      {
        directionn = Lgo; //turn left
      }
  
      if(Lspeedd <= Rspeedd) //if left distance equal to or less than right
      {
        directionn = Rgo; //turn right 
      } 
  
      if (Lspeedd < 10 && Rspeedd < 10) //if both distance less 10cm in right and left
      {
        back(10);
        detection(1);
      } 
    }
    else //distance larger than 25cm in front
    {
      directionn = Fgo; //go forward
    }
  }else{
    stopp(1); // clear output
    ask_pin_L(); // read distance in right
    delay(delay_time); // wait servo motor stability
    ask_pin_R(); // read distance in right  
    delay(delay_time); // wait servo motor stability

    delay(delay_servo);

    directionn = Lgo;
  
    if(Lspeedd <= Rspeedd) //if left distance equal to or less than right
    {
      directionn = Rgo; //turn right 
    } 
  }
}   
//*********************************************************************************
void ask_pin_F() // measure distance in front
{
  myservo.write(90);
  delay(delay_servo);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);  // delay de 2 microssegundos
  //seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1
  digitalWrite(trigPin, HIGH);
  //delay de 10 microssegundos
  delayMicroseconds(10);
  //seta o pino 12 com pulso baixo novamente
  digitalWrite(trigPin, LOW);
  // função Ranging, faz a conversão do tempo de
  //resposta do echo em centimetros, e armazena
  //na variavel distancia
  int Fdistance = (ultrasonic.Ranging(CM));

  
/*  digitalWrite(trigPin, LOW); // echo low level in 2us
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // echo high level 10us at least 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // keep echo low level
  float Fdistance = pulseIn(echoPin, HIGH); // read time
  Fdistance= Fdistance/5.8/10; // turn time to distance(mm)
  */
  Serial.print("F distance:"); //
  Serial.println(Fdistance); //
  Fspeedd = Fdistance; // 
} 
//********************************************************************************
void ask_pin_L() // measure distance in left 
{
  myservo.write(165);
  delay(delay_servo);
  digitalWrite(trigPin, LOW); // 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // 
  int Ldistance = (ultrasonic.Ranging(CM));
  //float Ldistance = pulseIn(echoPin, HIGH); // 
  //Ldistance= Ldistance/5.8/10; // 
  Serial.print("L distance:"); //
  Serial.println(Ldistance); //
  Lspeedd = Ldistance; // 
} 
//******************************************************************************
void ask_pin_R() // measure distance in right
{
  myservo.write(34);
  delay(300);
  digitalWrite(trigPin, LOW); // 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // 
  int Rdistance = (ultrasonic.Ranging(CM));
  //float Rdistance = pulseIn(echoPin, HIGH); //
  //Rdistance= Rdistance/5.8/10; // 
  Serial.print("R distance:"); //
  Serial.println(Rdistance); //
  Rspeedd = Rdistance; // 
} 
//*********************************************(LOOP)
void loop() 
{
  SL = digitalRead(SensorLeft);
  SM = digitalRead(SensorMiddle);
  SR = digitalRead(SensorRight);
//***********************************************normal remote control mode     
  //Serial.println(irrecv.decode(&results));
  int serialcom = Serial.read();

  if(serialcom == '1'){
    advance(10);
  }
  if(serialcom == '2'){
    back(10);
  }
  if(serialcom == '3'){
    right(10);
  }
  if(serialcom == '4'){
    left(10);
  }
    if(serialcom == '5'){
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,LOW);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
  }
  
  if (irrecv.decode(&results)) 
  Serial.println(irrecv.decode(&results));
  {         // encode success ,recive a cluster of infrared signal
/***********************************************************************/
    Serial.println(results.value, HEX);
    if (results.value == IRfront)//go forward
    {
      advance(10);//go forward
    }
/***********************************************************************/ 
    if (results.value ==  IRback)//go back
    {
      back(10);//go back
    }
/***********************************************************************/
    if (results.value == IRturnright)//turn right
    {
      right(6); // turn right
    }
/***********************************************************************/
    if (results.value == IRturnleft)//turn left
    {
      left(6); // turn left 
    }
/***********************************************************************/    
    if (results.value == IRstop)//stop
    {
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,LOW);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
    }
//****************************cny70 automatic move mode
    if (results.value == IRcny70)
    {                     
      while(IRcny70)
      {  
        SL = digitalRead(SensorLeft);
        SM = digitalRead(SensorMiddle);
        SR = digitalRead(SensorRight);

        Serial.print("L: ");
        Serial.print(SL);
        Serial.print(" - M: ");
        Serial.print(SM);
        Serial.print(" - R: ");
        Serial.println(SR);
        
        if (SM == HIGH)//middle sensor in black area
        { 
          if (SL == LOW & SR == HIGH) // left sensor in black area,right sensor in white area ,turn left
          {  
            Serial.println("esquerdo");  
            digitalWrite(MotorRight1,LOW);
            digitalWrite(MotorRight2,HIGH);
            digitalWrite(MotorLeft1,HIGH);
            digitalWrite(MotorLeft2,LOW);
          } 
          else if (SR == LOW & SL == HIGH) //left in white ,right in black ,turn right
          {  
            Serial.println("direito");
            digitalWrite(MotorRight1,HIGH);
            digitalWrite(MotorRight2,LOW);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,HIGH);
          }
           else  // both right and left in back, go forward
          {
            Serial.println("NENHUM");
            digitalWrite(MotorRight1,LOW);
            digitalWrite(MotorRight2,LOW);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,LOW);
          }      
        } 
        else // moddle sensor in white area
        {  
          if (SL == LOW & SR == HIGH)// left white ,right black, turn left to go foward
          {
            Serial.println("meio e esquerdo");  
            digitalWrite(MotorRight1,LOW);
            digitalWrite(MotorRight2,LOW);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,HIGH);
          }
          else if (SR == LOW & SL == HIGH)// right white, left black, turn right to go foward
          {  
            Serial.println("meio e direito");  
            digitalWrite(MotorRight1,LOW);
            digitalWrite(MotorRight2,HIGH);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,LOW);
          }
          else //both right and left in white ,stop
          {    
            Serial.println("só no meio");
            digitalWrite(MotorRight1,LOW);
            digitalWrite(MotorRight2,HIGH);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,HIGH);
          }
        }
        if (irrecv.decode(&results))
        {
           irrecv.resume(); 
           Serial.println(results.value,HEX);
           if(results.value ==IRstop)
           { 
             digitalWrite(MotorRight1,HIGH);
             digitalWrite(MotorRight2,HIGH);
             digitalWrite(MotorLeft1,HIGH);
             digitalWrite(MotorLeft2,HIGH);
             break;
           }
         }
       }
       //results.value=0;
       delay(1000);
    }
//**************************************ultrasonic automatic move mode
/*
 * AQUI
 */
    if (results.value ==IRAutorun )
    {
      while(IRAutorun)
      {
        myservo.write(90); //reset servo motor ,ready for next measure
        detection(); //measure angle ,And determine which direction to go to
        if(directionn == 8) // 8(go forward) 
        { 
          if (irrecv.decode(&results))
          {
            irrecv.resume(); 
            Serial.println(results.value,HEX);
            if(results.value ==IRstop)
            { 
              digitalWrite(MotorRight1,LOW); 
              digitalWrite(MotorRight2,LOW);
              digitalWrite(MotorLeft1,LOW);
              digitalWrite(MotorLeft2,LOW);
              break;
            }
          }
         // results.value=0;
          advance(1); // normal go forward 
          Serial.print(" Advance "); //
          Serial.print(" "); 
        }
        if(directionn == 2) // 2(go back) 
        {
          if (irrecv.decode(&results))
          {
            irrecv.resume(); 
            Serial.println(results.value,HEX);
            if(results.value ==IRstop)
            { 
              digitalWrite(MotorRight1,LOW); 
              digitalWrite(MotorRight2,LOW);
              digitalWrite(MotorLeft1,LOW);
              digitalWrite(MotorLeft2,LOW);
              break;
            }
          }
          //results.value=0;
          back(8); // 
          turnL(3); //
          Serial.print(" Reverse "); //
        }
        if(directionn == 6) //6(turn right ) 
        {
          if (irrecv.decode(&results))
          {
            irrecv.resume(); 
            Serial.println(results.value,HEX);
            if(results.value ==IRstop)
            { 
              digitalWrite(MotorRight1,LOW); 
              digitalWrite(MotorRight2,LOW);
              digitalWrite(MotorLeft1,LOW);
              digitalWrite(MotorLeft2,LOW);
              break;
            }
          }
          //results.value=0;
          back(1); 
          turnR(6); // 
          Serial.print(" Right "); //
        }
        if(directionn == 4) // 4(turn left) 
        { 
          if (irrecv.decode(&results))
          {
            irrecv.resume(); 
            Serial.println(results.value,HEX);
            if(results.value ==IRstop)
            { 
              digitalWrite(MotorRight1,LOW); 
              digitalWrite(MotorRight2,LOW);
              digitalWrite(MotorLeft1,LOW);
              digitalWrite(MotorLeft2,LOW);
              break;
            }
          }
          //results.value=0;
          back(1); 
          turnL(6); // 
          Serial.print(" Left "); //
        }
        
        if (irrecv.decode(&results))
        {
          irrecv.resume(); 
          Serial.println(results.value,HEX);
          if(results.value ==IRstop)
          {
            digitalWrite(MotorRight1,LOW); 
            digitalWrite(MotorRight2,LOW);
            digitalWrite(MotorLeft1,LOW);
            digitalWrite(MotorLeft2,LOW);
            break;
          }
        }
      }
      //results.value=0;
    }
    /***********************************************************************/    
    else
    {
      digitalWrite(MotorRight1,LOW);
      digitalWrite(MotorRight2,LOW);
      digitalWrite(MotorLeft1,LOW);
      digitalWrite(MotorLeft2,LOW);
    }
          
          
    irrecv.resume();    // Continue to recive a set of infrared signal        
  }
}
   

