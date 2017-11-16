
#include <Arduino.h>
#include <Keyboard.h>
#include <IRremote.h>
int RECV_PIN = 2;
int LED_PIN = 4;
//int PWM1_PIN = 10;

const int ledAzul = 9; 
const int ledVerde = 10;
const int ledVermelho = 5;
const int ledBranco = 3;

int azul = 0;
int verde = 0;
int vermelho = 0;
int branco = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

///////////////////////////////// USER IR REMOTE CODE ///////////////////////
/*
 //CONTROLE PIONEER
#define PLAY_PAUSE     0XB54A1AE5 
#define EXIT           0XB54A58A7
#define NEXT           0XB54AB04F
#define PRVS           0XF50AE619
#define FSCREEN        0XF50AB649
#define VOLUME_UP      0XB54A50AF
#define VOLUME_DN      0XB54AD02F
#define ESC            0XB54A48B7
#define MUTE           0XF50A0CF3
#define LEFT           0XB54A42BD
#define RIGHT          0XB54AC23D 
#define UP             0XB54A02FD
#define DOWN           0XB54A827D
#define ENTER          0XF50A34CB
*/

//CONTROLE PLACA CHINA LCD
#define PLAY_PAUSE     0XFE6A95  //0XFEA25D
#define EXIT           0XFE48B7
#define NEXT           0XFE6A95
#define PRVS           0XFE827D
#define FSCREEN        0XFE28D7  //  AUTO
#define VOLUME_UP      0XFE926D  //AV
#define VOLUME_DN      0XFE32CD  //TV
#define ESC            0XFE5AA5  //INFO
#define BACKSPACE      0XFEAA55  //SOURCE
#define MUTE           0XFE08F7
#define LEFT           0XFE7887
#define RIGHT          0XFE58A7 
#define UP             0XFED827
#define DOWN           0XFEF807
#define ENTER          0XFEE817


///////////////////////////  SETUP //////////////////////////////////////
void setup() 
{ 
  Serial.begin(57600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED_PIN, OUTPUT);
  pinMode(ledAzul,OUTPUT);   
  pinMode(ledVerde,OUTPUT);   
  pinMode(ledVermelho,OUTPUT);
  pinMode(ledBranco,OUTPUT);    
  Keyboard.begin();
  analogWrite(ledAzul,azul);     
  analogWrite(ledVerde,verde);
  analogWrite(ledVermelho,vermelho);
  analogWrite(ledBranco,branco);
  delay(2000);
}
////////////////////////// main prog ////////////////////////////////////
void loop()
{
    if (irrecv.decode(&results)) 
    {
     digitalWrite(LED_PIN,1); 
     
 /////////////////// ADD YOUR FUNCTIO0N HERE //////////////////////////      
  
  
  if (results.value==PLAY_PAUSE)  {Keyboard.write(' ');} 
  else if (results.value==EXIT)      {Keyboard.press(KEY_LEFT_ALT);  delay(10); Keyboard.press(KEY_F4); delay(10);  Keyboard.releaseAll();}  
  else if (results.value==NEXT)        {Keyboard.write('n'); delay(10); Keyboard.press(KEY_RIGHT_SHIFT);  Keyboard.press(KEY_RIGHT_ARROW);    delay(10);  Keyboard.releaseAll();}   
  else if (results.value==PRVS)        {Keyboard.write('p'); delay(10); Keyboard.press(KEY_RIGHT_SHIFT);  Keyboard.press(KEY_LEFT_ARROW);    delay(10);  Keyboard.releaseAll();}   
  else if (results.value==FSCREEN)        {Keyboard.write('f');}   
  else if (results.value==ENTER)       {Keyboard.write(KEY_RETURN);delay(10); Keyboard.releaseAll();}   
  else if (results.value==VOLUME_UP)   {Keyboard.press(KEY_RIGHT_CTRL);   Keyboard.press(KEY_RIGHT_ALT);    Keyboard.press(KEY_F10);   delay(10);  Keyboard.releaseAll(); Keyboard.press('+');   delay(10);  Keyboard.releaseAll();}   
  else if (results.value==VOLUME_DN)   {Keyboard.press(KEY_RIGHT_CTRL);   Keyboard.press(KEY_RIGHT_ALT);  Keyboard.press(KEY_F9);   delay(10);  Keyboard.releaseAll(); Keyboard.press('-');   delay(10);  Keyboard.releaseAll();}   
  else if (results.value==ESC)        {Keyboard.press(KEY_ESC);   delay(10);  Keyboard.releaseAll();   delay(10); Keyboard.press(KEY_BACKSPACE);   delay(10);  Keyboard.releaseAll();} 
  else if (results.value==BACKSPACE)        {Keyboard.press(KEY_BACKSPACE);   delay(10);  Keyboard.releaseAll();}
  else if (results.value==MUTE)       {Keyboard.press(KEY_RIGHT_CTRL);   Keyboard.press(KEY_RIGHT_ALT);  Keyboard.press(KEY_F11);   delay(10);  Keyboard.releaseAll();} 
  else if (results.value==UP)          {Keyboard.press(KEY_UP_ARROW); Keyboard.releaseAll();}   
  else if (results.value==DOWN)        {Keyboard.press(KEY_DOWN_ARROW); Keyboard.releaseAll();}  
  else if (results.value==LEFT)        {Keyboard.press(KEY_LEFT_ARROW); Keyboard.releaseAll();}  
  else if (results.value==RIGHT)       {Keyboard.press(KEY_RIGHT_ARROW); Keyboard.releaseAll();} 
  
  else if (results.value==0XFE807F)       {azul = azul+25;} 
  else if (results.value==0XFE20DF)       {azul = azul-25;} 
  else if (results.value==0XFE40BF)       {verde = verde+25;} 
  else if (results.value==0XFEA05F)       {verde = verde-25;} 
  else if (results.value==0XFEC03F)       {vermelho = vermelho+25;} 
  else if (results.value==0XFE609F)       {vermelho = vermelho-25;} 
  else if (results.value==0XFEE01F)       {azul = azul-25; verde = verde-25; vermelho = vermelho-25;} 
  else if (results.value==0XFE10EF)       {azul = azul+25; verde = verde+25; vermelho = vermelho+25;} 
  else if (results.value==0XFE906F)       {
    if(azul==0 and verde==0 and vermelho==0) 
      {azul=50; verde=50; vermelho=50;}
    else 
      {azul=0; verde=0; vermelho=0;} 
    }

  else if (results.value==0XFED02F)       {
    if(branco==0) 
      {branco=50;}
    else 
      {branco=0;} 
  }
  else if (results.value==0XFE00FF)       {branco = branco+25;} 
  else if (results.value==0XFE52AD)       {branco = branco-25;} 

  analogWrite(ledAzul,azul);     
  analogWrite(ledVerde,verde);
  analogWrite(ledVermelho,vermelho);
  analogWrite(ledBranco,branco);

   Serial.print("   |   ");
   Serial.println(results.value, HEX);       //ir code 
   delay(100); 
   digitalWrite(LED_PIN,0); 
   irrecv.resume(); // Receive the next value
    }
}

