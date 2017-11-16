#include <Arduino.h>
#include <IRremote.h>
#include <SPI.h>
#include "RF24.h"
#include "Mouse.h"
#include <Keyboard.h>

//Armazena os dados recebidos
int recebidos[15];

int RECV_PIN = 2;

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do Arduino
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;


int range = 25;

int rangeGyro = 70;
int rangex = 0;  
int rangey = 0;
int gx = 0; int gy = 0; int gx1 = 0; int gy1 = 0; int gx2 = 0; int gy2 = 0; int gx3 = 0; int gy3 = 0; int gx4 = 0; int gy4 = 0;
int gx5 = 0; int gy5 = 0; int gx6 = 0; int gy6 = 0;
int ax = 0; int ay = 0; int ax1 = 0; int ay1 = 0; int ax2 = 0; int ay2 = 0; int ax3 = 0; int ay3 = 0; int ax4 = 0; int ay4 = 0;
int ax5 = 0; int ay5 = 0; int ax6 = 0; int ay6 = 0;
int mapeado = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

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


void setup()
{

  //Inicializa a serial
  Serial.begin(115200);
   irrecv.enableIRIn(); // Start the receiver
// while (!Serial) {
//; // aguarde a serial conectar. Somente necessário para o Leonardo
//}
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de recepcao
  radio.openReadingPipe(1,pipe);
  delay(100);
  radio.startListening();

  Serial.println("Aguardando dados...");
  Mouse.begin();
  Keyboard.begin();
}

void loop()
{

  if (irrecv.decode(&results)) 
    {

  if (results.value==PLAY_PAUSE)  {Keyboard.write(' ');} 
    else if (results.value==EXIT)      {Keyboard.press(KEY_LEFT_ALT);  delay(10); Keyboard.press(KEY_F4); delay(10);  Keyboard.releaseAll();}  
    else if (results.value==NEXT)        {Keyboard.write('n'); delay(10); Keyboard.press(KEY_RIGHT_SHIFT);  Keyboard.press(KEY_RIGHT_ARROW);    delay(10);  Keyboard.releaseAll();}   
    else if (results.value==PRVS)        {Keyboard.write('p'); delay(10); Keyboard.press(KEY_RIGHT_SHIFT);  Keyboard.press(KEY_LEFT_ARROW);    delay(10);  Keyboard.releaseAll();}   
    else if (results.value==FSCREEN)        {Keyboard.write('f');}   
    else if (results.value==ENTER)       {Keyboard.write(KEY_RETURN);delay(10); Keyboard.releaseAll();}   
    else if (results.value==VOLUME_UP)   {Keyboard.press(KEY_RIGHT_CTRL);   Keyboard.press(KEY_RIGHT_ALT);    Keyboard.press(KEY_F10);   delay(10);  Keyboard.releaseAll(); Keyboard.press('+');   delay(10);  Keyboard.releaseAll();}   
    else if (results.value==VOLUME_DN)   {Keyboard.press(KEY_RIGHT_CTRL);   Keyboard.press(KEY_RIGHT_ALT);  Keyboard.press(KEY_F9);   delay(10);  Keyboard.releaseAll(); Keyboard.press('-');   delay(10);  Keyboard.releaseAll();}   
    else if (results.value==ESC)        {Keyboard.press(KEY_ESC);   delay(10);  Keyboard.releaseAll();   delay(10); Keyboard.press(KEY_BACKSPACE);   delay(10);  Keyboard.releaseAll();} 
    //else if (results.value==BACKSPACE)        {Keyboard.press(KEY_BACKSPACE);   delay(10);  Keyboard.releaseAll();}
    else if (results.value==MUTE)       {Keyboard.press(KEY_RIGHT_CTRL);   Keyboard.press(KEY_RIGHT_ALT);  Keyboard.press(KEY_F11);   delay(10);  Keyboard.releaseAll();} 
    else if (results.value==UP)          {Keyboard.press(KEY_UP_ARROW); Keyboard.releaseAll();}   
    else if (results.value==DOWN)        {Keyboard.press(KEY_DOWN_ARROW); Keyboard.releaseAll();}  
    else if (results.value==LEFT)        {Keyboard.press(KEY_LEFT_ARROW); Keyboard.releaseAll();}  
    else if (results.value==RIGHT)       {Keyboard.press(KEY_RIGHT_ARROW); Keyboard.releaseAll();} 
  
  
    // Serial.print("   |   ");
    Serial.println(results.value, HEX);
  
  irrecv.resume();
  }


//####################################################################################################################################################################

  
  if (radio.available())
  {
    bool done = false;    
    while (!done)
    {
      gx6 = gx5; gx5 = gx4; gx4 = gx3; gx3 = gx2; gx2 = gx1; gx1 = gx;
      gy6 = gy5; gy5 = gy4; gy4 = gy3; gy3 = gy2; gy2 = gy1; gy1 = gy;
     
      ax6 = ax5; ax5 = ax4; ax4 = ax3; ax3 = ax2; ax2 = ax1; ax1 = ax;
      ay6 = ay5; ay5 = ay4; ay4 = ay3; ay3 = ay2; ay2 = ay1; ay1 = ay;
    
      done = radio.read(recebidos, sizeof(recebidos));

       int mapeado = map(recebidos[0], 150, 600, 0, 40);
      Serial.print("  st  "); Serial.print(mapeado);
 //     Serial.print("  st  "); Serial.print(recebidos[0]);
      Serial.print("     b1  "); Serial.print(recebidos[1]);
      Serial.print("     b2  "); Serial.print(recebidos[2]);
      Serial.print("     sc  "); Serial.print(recebidos[3]);
      Serial.print("     set  "); Serial.print(recebidos[4]);
      Serial.print("     ax  "); Serial.print(recebidos[5]);
      Serial.print("     ay  "); Serial.print(recebidos[6]);
      Serial.print("     az  "); Serial.print(recebidos[7]);
      Serial.print("     gx  "); Serial.print(recebidos[8]);
      Serial.print("     gy  "); Serial.print(recebidos[9]);
      Serial.print("     gz  "); Serial.println(recebidos[10]);

      //mouse
     gx = map(recebidos[10], -330, 330, -rangeGyro, rangeGyro);
     gy = map(recebidos[9], -330, 330, -rangeGyro, rangeGyro);
     
     int mgx = (gx+gx1+gx2+gx3+gx4+gx5+gx6)/7;
     int mgy = (gy+gy1+gy2+gy3+gy4+gy5+gy6)/7;

     rangex = (range + abs(mgy));
     rangey = (range + abs(mgx));


     ax = map(recebidos[7], -1700, 1700, -rangex, rangex);
     ay = map(recebidos[6], -1700, 1700, rangey, -rangey);

     int mx = (ax+ax1+ax2+ax3+ax4+ax5+ax6)/8;
     int my = (ay+ay1+ay2+ay3+ay4+ay5+ay6)/8;

     int setas = recebidos[4];
      if(setas == 1) {Mouse.move(0, 0, -1); delay(50);}
      else if(setas == 2) {Mouse.move(0, 0, 1); delay(50);}
      else if(setas == 3) {Keyboard.write(KEY_RETURN); Keyboard.releaseAll(); delay(100);}
      else if(setas == 4) {Keyboard.press(KEY_UP_ARROW); Keyboard.releaseAll(); delay(100);}
      else if(setas == 5) {Keyboard.press(KEY_LEFT_ARROW); Keyboard.releaseAll(); delay(100);}
      else if(setas == 6) {Keyboard.press(KEY_RIGHT_ARROW); Keyboard.releaseAll(); delay(100);}
      else if(setas == 7) {Keyboard.press(KEY_DOWN_ARROW); Keyboard.releaseAll(); delay(100);}
      else if(setas == 8) {Keyboard.press(KEY_BACKSPACE); Keyboard.releaseAll(); delay(100);}
        

         
     if(recebidos[1] == 1) {Mouse.press(MOUSE_LEFT);delay(20);}
     else {Mouse.release();}

     if(recebidos[2] == 1) {Mouse.click(MOUSE_RIGHT); delay(300);}

    if(mapeado > 5){
      Mouse.move(mx, my, 0);
      
     delay(4);
    }
    
    }
}
}


