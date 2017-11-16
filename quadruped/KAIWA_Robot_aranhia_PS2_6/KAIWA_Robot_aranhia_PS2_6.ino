  //--------------------------------------------------------------
// Stompy the Robot - Mk 1 - APC Magazine, July 2013 issue
//
// Modified by Darren Yates 3 May 2013
// From code originally developed by Russell Cameron, Dagu.
// Editado y comentado por Konrad PEschka, Bs As, 2015
//--------------------------------------------------------------

#include <Servo.h>
#include <NewPing.h>
#include <PS2X_lib.h> 

PS2X ps2x; // create PS2 Controller Class

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 400
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

//-------------------------------------------------------------------
//Con este timer se setea la velocidad de movimiento de todo el robot, mas chico, mas rapido
//-------------------------------------------------------------------

int Time=100;

//-------------------------------------------------------------------
//  Definicion de las constantes posicion inicial de cada servo
//-------------------------------------------------------------------

//subir = giro antihor en cuerpo y patas

#define FIC_centro      1100     //Frente_Izquierda_cuerpo_centro
#define FDC_centro      1700     //Frente_derecha_cuerpo_centro
#define AIC_centro      1800     //Atras_Izquierda_cuerpo_centro
#define ADC_centro      1250     //Atras_derecha_cuerpo_centro

#define FIP_centro      800      //Frente_Izquierda_pata_centro
#define FDP_centro      800      //Frente_derecha_pata_centro
#define AIP_centro      700      //Atras_Izquierda_pata_centro
#define ADP_centro      600      //Atras_derecha_pata_centro

//-------------------------------------------------------------------
//      Definicion Alias de cada servo y los Pines del Arduino
//-------------------------------------------------------------------

#define FIC_pin 4      // Pin Frente Izquierda Cuerpo
#define FDC_pin 7      // Pin Frente Derecha Cuerpo
#define AIC_pin 5      // Pin Atras Izquierda Cuerpo
#define ADC_pin 6      // Pin Atras Derecha Cuerpo

#define FIP_pin 8      // Pin Frente Izquierda Pata
#define FDP_pin 11     // Pin Frente Derecha Pata
#define AIP_pin 9      // Pin Atras Izquierda Pata
#define ADP_pin 10     // Pin Atras Derecha Pata

#define Cabeza_pin 3

#define pulsador_arranque 12  //defino donde va conectado el pulsador de arranque

//#define debug                  //comentando o descomentando esta linea activo el codigo para debug


//-------------------------------------------------------------------

int movimiento_izq;
int movimiento_der;
int levanta=-400;

int contador_sentarse;
int distancia_actual = 0;
int pos = 90;

int max_der = 0;
int max_izq = 0;
int aux=0;    //auxiliar que utilizo para las funciones especiales
int variable_sienta=800;

const int tiempo_entre_servo=5;
const int tiempo_sienta=50;

const int margen_joystick=10;      //margen que tiene el joystick para saber si esta corrido del centro

int variable_control=0;   //variable que indica que comando fue pulsado en el PS2

//-------------------------------------------------------------------
//       Defino como le va a llamar cada servo
//-------------------------------------------------------------------

Servo FIC_servo;                                               // Front Left  Hip
Servo FDC_servo;                                               // Front Right Hip
Servo AIC_servo;                                               // Rear  Left  Hip
Servo ADC_servo;                                               // Rear  Right Hip
Servo FIP_servo;                                               // Front Left  Knee
Servo FDP_servo;                                               // Front Right Knee
Servo AIP_servo;                                               // Rear  left  Knee
Servo ADP_servo;                                               // Rear  Right Knee

Servo Cabeza_servo;

//-------------------------------------------------------------------
//                 Seteo de Entradas, salidas y funciones
//-------------------------------------------------------------------

void setup()
{
  
  //-------------------------------------------------------------------
  // Inicializo Los servos con los nombres y cual es su pin asociado
  //-------------------------------------------------------------------

 #ifdef debug
   Serial.begin(9600);
 #endif
   
  FIC_servo.attach(FIC_pin);           //define los servos con su pin
  FDC_servo.attach(FDC_pin);  
  AIC_servo.attach(AIC_pin);  
  ADC_servo.attach(ADC_pin);  
  FIP_servo.attach(FIP_pin);  
  FDP_servo.attach(FDP_pin);  
  AIP_servo.attach(AIP_pin);  
  ADP_servo.attach(ADP_pin); 
  Cabeza_servo.attach(Cabeza_pin); 

ps2x.config_gamepad(A2,A4,A3,A5, true, true);   //clock, command, attention, data
//-------------------------------------------------------------------
//         Arranco Todos los Servos en sus posiciones iniciales
//-------------------------------------------------------------------


  FIC_servo.writeMicroseconds(FIC_centro);       // envia servo a su posicion inicial
  delay(tiempo_entre_servo);
  FDC_servo.writeMicroseconds(FDC_centro); 
  delay(tiempo_entre_servo); 
  AIC_servo.writeMicroseconds(AIC_centro);  
  delay(tiempo_entre_servo);
  ADC_servo.writeMicroseconds(ADC_centro);  
  delay(tiempo_entre_servo);
  FIP_servo.writeMicroseconds(FIP_centro);  
  delay(tiempo_entre_servo);
  FDP_servo.writeMicroseconds(FDP_centro);  
  delay(tiempo_entre_servo);
  AIP_servo.writeMicroseconds(AIP_centro);  
  delay(tiempo_entre_servo);
  ADP_servo.writeMicroseconds(ADP_centro); 
  delay(tiempo_entre_servo);
  Cabeza_servo.write(90);

delay(500);  
}

//-------------------------------------------------------------------
//         Sector donde comienza la funcion Principal,
//        Donde se va a quedar el resto de la ejecucion
//-------------------------------------------------------------------
  
void loop()
{
  //checkPath();
  
 // while(digitalRead(pulsador_arranque)==0)
  //;
  
  while(1)   //se queda en este loop luego de haber pulsado el pulsador de arranque
  {

    lectura_control();  //lectura del control PS2
    #ifdef debug
          Serial.println("PS2=");
          Serial.println(variable_control);
    #endif   
    
    
    if(variable_control==0)  //si no llegan comandos de la PS2 hago nada
    {
      posicion_reposo();       
    }
    
//-------------comandos de habilidades especiales----------------------------

//--------------------------se pulsa triangulo  ---------------------------------
    
        while(variable_control==7)  //fue pulsado triangulo
        {
           if(aux==0)
           sienta();
           aux=1;
           delay(10);
           lectura_control();
           
           while(variable_control==7)  //fue pulsado triangulo
           {
            delay(10);
           lectura_control();
           }
        }
        
         if(aux==1)
         {
          sentado_levanta();
          aux=0;
          delay(300);
         }

//--------------------------se pulsa circulo  ---------------------------------
         
        while(variable_control==8)  //fue pulsado circulo
        {
          if(aux==0)
          saluda();
          aux=1;
          delay(10);
          lectura_control();
          
           while(variable_control==8)  //fue pulsado circulo
           {
            delay(10);
            mueve_pata_frente();
           lectura_control();
           }
        }
         if(aux==1)
         {
          saluda_levanta();
          aux=0;
          delay(300);
        }

//--------------------------se pulsa X   ---------------------------------

        while(variable_control==9)  //fue pulsado X
        {
          if(aux==0)
          alaba();
          aux=1;
          delay(10);
          lectura_control();
          
           while(variable_control==9)  //fue pulsado x
           {
            delay(10);
           lectura_control();
           }
        }
         if(aux==1)
         {
          alaba_levanta();
          aux=0;
          delay(300);
        }

//--------------------------se pulsa Cuadrado   ---------------------------------

        while(variable_control==10)  //fue pulsado cuadrado
        {
          if(aux==0)
          angelito_cae();
          aux=1;
          delay(10);
          lectura_control();
          
           while(variable_control==10)  //fue pulsado cuadrado
           {
            delay(10);
            angelito_saluda();
           lectura_control();
           }
        }
         if(aux==1)
         {
         // angelito_levanta();
          aux=0;
          delay(300);
        }

//-------------------comandos de movimientos normales--------------------
        
    if(variable_control==11)  //fue pulsado arriba
    {
       movimiento_izq=-300;
      movimiento_der=-300;
      Camina_frente();
    }
    if(variable_control==12)  //fue pulsado abajo
    {
      camina_atras();
    }
    if(variable_control==13) //fue pulsado izquierda
    {
      Gira_der() ; 
    }
    if(variable_control==14)  //fue pulsado derecha
    {
      Gira_izq(); 
    }
       

//----------------comando aumento y disminucion de velocidad--------------------------

    if(variable_control==23)  //si no llegan comandos de la PS2 hago nada
    {
      Time=Time+20;   
      if(Time>240)
      Time=240;   
    }

    if(variable_control==24)  //si no llegan comandos de la PS2 hago nada
    {
      Time=Time-20;   
      if(Time<10)
      Time=10;   
    }
  }
  
}

//-------------------------------------------------------------------
//            Sector definicion delas Funciones Utilizadas
//-------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//       funcion para volver a la posicion inicial despues de cada movimiento
//-------------------------------------------------------------------------------------

void posicion_reposo(void)
{
  int tiempo=20;
   FIC_servo.writeMicroseconds(FIC_centro);       // envia servo a su posicion inicial
  delay(tiempo);
  FDC_servo.writeMicroseconds(FDC_centro); 
  delay(tiempo);
  AIC_servo.writeMicroseconds(AIC_centro);  
  delay(tiempo);
  ADC_servo.writeMicroseconds(ADC_centro);  
  delay(tiempo);
  FIP_servo.writeMicroseconds(FIP_centro);  
  delay(tiempo);
  FDP_servo.writeMicroseconds(FDP_centro);  
  delay(tiempo);
  AIP_servo.writeMicroseconds(AIP_centro);  
  delay(tiempo);
  ADP_servo.writeMicroseconds(ADP_centro); 
  delay(tiempo);
  Cabeza_servo.write(90);
}

//-------------------------------------------------------------------
//             Funcion Avanzar hacia el frente
//-------------------------------------------------------------------
void Camina_frente()
{

  if (movimiento_izq<0 && movimiento_der<0) 
   { 
    Cabeza_servo.write(110); 
    decide_costados(); 
   }
   
  FDP_servo.writeMicroseconds(FDP_centro-levanta);                // raise front right leg 
  delay(tiempo_entre_servo);
  AIP_servo.writeMicroseconds(AIP_centro-levanta);                // raise rear  left  leg
  delay(tiempo_entre_servo);
  FIC_servo.writeMicroseconds(FIC_centro-movimiento_izq);         // move  front left  leg backward
  delay(tiempo_entre_servo);
  ADC_servo.writeMicroseconds(ADC_centro+movimiento_der);         // move  rear  right leg backward
  delay(Time/2);
  FDC_servo.writeMicroseconds(FDC_centro-movimiento_der);         // move  front right leg forward
  delay(tiempo_entre_servo);
  AIC_servo.writeMicroseconds(AIC_centro+movimiento_izq);         // move  rear  left  leg forward
  delay(Time);
  FDP_servo.writeMicroseconds(FDP_centro);                        // lower front right leg 
  delay(tiempo_entre_servo);
  AIP_servo.writeMicroseconds(AIP_centro);                        // lower rear  left  leg
  delay(Time);
  
  if (movimiento_izq<0 && movimiento_der<0) 
   { 
    Cabeza_servo.write(70);
    decide_costados(); 
    }
    
  FIP_servo.writeMicroseconds(FIP_centro-levanta);                // raise front left  leg
  delay(tiempo_entre_servo);
  ADP_servo.writeMicroseconds(ADP_centro-levanta);                // raise rear  right leg
  delay(tiempo_entre_servo);
  FDC_servo.writeMicroseconds(FDC_centro+movimiento_der);         // move  front right leg backward
  delay(tiempo_entre_servo);
  AIC_servo.writeMicroseconds(AIC_centro-movimiento_izq);         // move  rear  left  leg backward
  delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro+movimiento_izq);         // move  front left  leg forward
  delay(tiempo_entre_servo);
  ADC_servo.writeMicroseconds(ADC_centro-movimiento_der);         // move  rear  right leg forward
  delay(Time);
  FIP_servo.writeMicroseconds(FIP_centro);                        // lower front left  leg
  delay(tiempo_entre_servo);
  ADP_servo.writeMicroseconds(ADP_centro);                        // lower rear  right leg
  delay(Time);  

  }
  
//-------------------------------------------------------------------
//            Funcion que lee el sensor frontal
//-------------------------------------------------------------------  
  
  int readPing()                            //funcion para leer US y pasarlo a cm
{
  unsigned int uS = sonar.ping();
  delay(50);
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}


//-------------------------------------------------------------------
//                    Elije para donde avanzar
//-------------------------------------------------------------------
int decide_costados() 
{
delay(50);
distancia_actual = readPing();

if (distancia_actual < 30 && distancia_actual > 5)       //chequeo si obstaculo esta entrte 10 y 30 cm
{ 
 mira_costados();                             //encontrar la salida
} 

if (distancia_actual < 6 && distancia_actual != 0)       //chequea obstaculo menor a 10cm
{ 
camina_atras();                               //hace secuancia para atras
}

}


//-------------------------------------------------------------------
//  Mide para lso costados para despues decidir hacia donde avanzar
//-------------------------------------------------------------------

int mira_costados()                          //hace un barrido y decide para donde ir
  {

  delay(90);                           
  max_der = 0; 
  max_izq = 0;
  
  for(pos = 144; pos >= 36; pos-= 36)     // goes from 180 degrees to 0 degrees 
  {
   Cabeza_servo.write(pos);                 // tell servo to go to position in variable 'pos' 
    delay(90);                      
    distancia_actual = readPing();                 //lee ultrasonido
    if (pos > 90 && distancia_actual > max_izq)    // si es mayor al maximo izquierda lo actualiza
    { 
    max_izq = distancia_actual;                     
    } 
    if (pos < 90 && distancia_actual > max_der)   // si es mayor al maximo derecha lo actualiza
    { 
    max_der = distancia_actual; 
    }
  }
  
  
   Cabeza_servo.write(90);                //posiciona servo en el medio
    if (max_der > max_izq) 
     { 
     Gira_der();                       //gira derecha
     }
    if (max_izq > max_der) 
     { 
      Gira_izq();                      //gira izquierda
     }
}
    
//-------------------------------------------------------------------
//                 Gira Derecha
//-------------------------------------------------------------------


void Gira_der() 
{
   movimiento_izq=300;
   movimiento_der=-300;
   Camina_frente();
}  

//-------------------------------------------------------------------
//                 Gira Izquierda
//-------------------------------------------------------------------

void Gira_izq() 
{
   movimiento_izq=-300;
   movimiento_der=300;
  Camina_frente();
}  

//-------------------------------------------------------------------
//               Camina hacia atras
//-------------------------------------------------------------------

void camina_atras()
{
   movimiento_izq=300;
  movimiento_der=300;
   Camina_frente();
}

//-------------------------------------------------------------------
//                  Funcion Sentarse
//-------------------------------------------------------------------
void sienta(void)
{
  
  FDC_servo.writeMicroseconds(FDC_centro);
  delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro);
  delay(Time/2);

  
  ADC_servo.writeMicroseconds(ADC_centro+variable_sienta/3);  //se tira de a poco
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro-variable_sienta/3);
  delay(Time/2);
  ADP_servo.writeMicroseconds(ADP_centro+variable_sienta/3);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta/3);
  delay(Time/2);
  
  ADC_servo.writeMicroseconds(ADC_centro+variable_sienta/2);  //se tira de a poco
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro-variable_sienta/2);
  delay(Time/2);
  ADP_servo.writeMicroseconds(ADP_centro+variable_sienta/2);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta/2);
  delay(Time/2);
  
  ADC_servo.writeMicroseconds(ADC_centro+variable_sienta);   //se termina de tirar
 delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro-variable_sienta);
  delay(Time/2);
  ADP_servo.writeMicroseconds(ADP_centro+variable_sienta);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta);
  delay(Time/2);
  
  delay(10);               
}  

void mueve_cabeza(void)
{
  Cabeza_servo.write(45);
  delay(3*Time);
  Cabeza_servo.write(135);
  delay(3*Time);
  Cabeza_servo.write(90);
 delay(3*Time);
}

void sentado_levanta(void)
{
  mueve_cabeza();
  
  FIP_servo.writeMicroseconds(FIP_centro); 
  delay(Time/2);
  FDP_servo.writeMicroseconds(FDP_centro); 
  delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro);  
  delay(Time/2);
  FDC_servo.writeMicroseconds(FDC_centro);  
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro); 
  delay(Time/2); 
  ADP_servo.writeMicroseconds(ADP_centro); 
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro);                      // center servos
  delay(Time/2);
  ADC_servo.writeMicroseconds(ADC_centro); 
  
  delay(10);
}


//-------------------------------------------------------------------
//                  Funcion Saluda
//-------------------------------------------------------------------

void saluda(void)
{
  FDC_servo.writeMicroseconds(FDC_centro);
  delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro);
  delay(Time/2);

  ADC_servo.writeMicroseconds(ADC_centro+variable_sienta);  //se tira al piso de costado
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro-variable_sienta);
  delay(Time/2);

  FDP_servo.writeMicroseconds(2550);
  delay(Time/2);
  ADP_servo.writeMicroseconds(ADP_centro+variable_sienta/3);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta/3);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta/2);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta);
  delay(Time/2);
  
  delay(10);
}  

void saluda_levanta(void)
{
 mueve_cabeza();
  
  
  FIP_servo.writeMicroseconds(FIP_centro); 
  delay(Time/2);
  FDP_servo.writeMicroseconds(FDP_centro); 
  delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro);  
  delay(Time/2);
  FDC_servo.writeMicroseconds(FDC_centro);  
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro); 
  delay(Time/2); 
  ADP_servo.writeMicroseconds(ADP_centro); 
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro);                      // center servos
  delay(Time/2);
  ADC_servo.writeMicroseconds(ADC_centro); 
  
  delay(10);
}

//-------------------------------------------------------------------
//                  Funcion Mueve Pata en Frente
//-------------------------------------------------------------------

void mueve_pata_frente(void)
{
  int maximo=500;
    for(int j=0;j<maximo;j=j+100)
  {
  FDC_servo.writeMicroseconds(FDC_centro+j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  FDC_servo.writeMicroseconds(FDC_centro+j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=0;j<maximo;j=j+100)
  {
  FDC_servo.writeMicroseconds(FDC_centro-j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  FDC_servo.writeMicroseconds(FDC_centro-j);  //se tira al piso de costado
  delay(Time/2);
  }
}


//-------------------------------------------------------------------
//                  Funcion Alaba y se queda abajo
//-------------------------------------------------------------------
void alaba(void)
{
  
  ADC_servo.writeMicroseconds(ADC_centro);
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro);
  delay(Time/2);

  FDC_servo.writeMicroseconds(FDC_centro+variable_sienta);   //se termina de tirar
 delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro-variable_sienta);
  delay(Time/2);
  FDP_servo.writeMicroseconds(FDP_centro+variable_sienta);
  delay(Time/2);
  FIP_servo.writeMicroseconds(FIP_centro+variable_sienta);
  delay(Time/2);
  
  delay(10);               
}  


void alaba_levanta(void)
{
  
  FIP_servo.writeMicroseconds(FIP_centro); 
  delay(Time/2);
  FDP_servo.writeMicroseconds(FDP_centro); 
  delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro);  
  delay(Time/2);
  FDC_servo.writeMicroseconds(FDC_centro);  
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro); 
  delay(Time/2); 
  ADP_servo.writeMicroseconds(ADP_centro); 
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro);                      // center servos
  delay(Time/2);
  ADC_servo.writeMicroseconds(ADC_centro); 
  
  delay(10);
}

//-------------------------------------------------------------------
//                  Funcion angelito
//-------------------------------------------------------------------
void angelito_cae(void)
{

  FDC_servo.writeMicroseconds(FDC_centro+variable_sienta);   //se termina de tirar
 delay(Time/2);
  FIC_servo.writeMicroseconds(FIC_centro-variable_sienta);
  delay(Time/2);
  FDP_servo.writeMicroseconds(FDP_centro+variable_sienta);
  delay(Time/2);
  FIP_servo.writeMicroseconds(FIP_centro+variable_sienta);
  delay(Time/2);

  ADC_servo.writeMicroseconds(ADC_centro-variable_sienta);   //se termina de tirar
  delay(Time/2);
  AIC_servo.writeMicroseconds(AIC_centro+variable_sienta);
  delay(Time/2);
  ADP_servo.writeMicroseconds(ADP_centro+variable_sienta);
  delay(Time/2);
  AIP_servo.writeMicroseconds(AIP_centro+variable_sienta);
  delay(Time/2);

}


void angelito_saluda(void)
{
    int maximo=600;
    for(int j=0;j<maximo;j=j+100)
  {
  FDC_servo.writeMicroseconds(FDC_centro+j);  //se tira al piso de costado
  FIC_servo.writeMicroseconds(FIC_centro-j);  //se tira al piso de costado
  ADC_servo.writeMicroseconds(ADC_centro-j);  //se tira al piso de costado
  AIC_servo.writeMicroseconds(AIC_centro+j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  FDC_servo.writeMicroseconds(FDC_centro+j);  //se tira al piso de costado
  FIC_servo.writeMicroseconds(FIC_centro-j);  //se tira al piso de costado
  ADC_servo.writeMicroseconds(ADC_centro-j);  //se tira al piso de costado
  AIC_servo.writeMicroseconds(AIC_centro+j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=0;j<maximo;j=j+100)
  {
  FDC_servo.writeMicroseconds(FDC_centro-j);  //se tira al piso de costado
  FIC_servo.writeMicroseconds(FIC_centro+j);  //se tira al piso de costado
  ADC_servo.writeMicroseconds(ADC_centro+j);  //se tira al piso de costado
  AIC_servo.writeMicroseconds(AIC_centro-j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  FDC_servo.writeMicroseconds(FDC_centro-j);  //se tira al piso de costado
  FIC_servo.writeMicroseconds(FIC_centro+j);  //se tira al piso de costado
  ADC_servo.writeMicroseconds(ADC_centro+j);  //se tira al piso de costado
  AIC_servo.writeMicroseconds(AIC_centro-j);  //se tira al piso de costado
  delay(Time/2);
  }
}
//-------------------------------------------------------------------------------------
void lectura_control(void)
{
         ps2x.read_gamepad(false, 0);          //read controller and set large motor to spin at 'vibrate' speed 
         
//-------------------------------------lectura de los Botones------------------------------------------------
        variable_control=0;

        if(ps2x.ButtonPressed(PSB_START))   
        {
          #ifdef debug
          Serial.println("Start");
          #endif    
          variable_control=1;     
          return;       
        }
         
        if(ps2x.ButtonPressed(PSB_SELECT))
        {
          #ifdef debug
          Serial.println("Select");
          #endif
          variable_control=2;
          return; 
        }
         

        if(ps2x.ButtonPressed(PSB_L3))
        {
          #ifdef debug
          Serial.println("L3");
          #endif
          variable_control=3;
          return; 
        }
         
         
        if(ps2x.ButtonPressed(PSB_R3))
        {
          #ifdef debug
          Serial.println("R3");
          #endif
          variable_control=4;
          return; 
        }
         
         
        if(ps2x.ButtonPressed(PSB_L2))
        {
          #ifdef debug
          Serial.println("L2");
          #endif
          variable_control=5;
          return; 
        }
         
         
        if(ps2x.Button(PSB_R2))
        {
          #ifdef debug
          Serial.println("R2");
          #endif
          variable_control=6;
          return; 
        }
         
         
         if(ps2x.Button(PSB_GREEN))  //triangulo
         {
          #ifdef debug
          Serial.println("Triangulo");
          #endif
           variable_control=7;
           return; 
         }
         
          
         if(ps2x.Button(PSB_RED))   //circulo
         {
          #ifdef debug
          Serial.println("Circulo");
          #endif
          variable_control=8;
          return; 
         }
         
          
         if(ps2x.Button(PSB_BLUE))   //x
         {
          #ifdef debug
          Serial.println("X");
          #endif
          variable_control=9;
          return; 
         }


         if(ps2x.Button(PSB_PINK))   //cuadrado
         {
          #ifdef debug
          Serial.println("Cuadrado");
          #endif
           variable_control=10;
           return; 
         }
        

        if(ps2x.Button(PSB_PAD_UP))       //boton arriba   
        {
          #ifdef debug
          Serial.println("Arriba");
          #endif   
          variable_control=11;  
          return;     
        }
         
         
        if(ps2x.Button(PSB_PAD_DOWN))     //boton abajo  
        {
          #ifdef debug
          Serial.println("Abajo");
          #endif  
          variable_control=12; 
          return;           
        }
         
         
        if(ps2x.Button(PSB_PAD_LEFT))   //boton izquierda     
        {
          #ifdef debug
          Serial.println("Izquierda");
          #endif  
          variable_control=13;
          return;          
        }
         
         
        if(ps2x.Button(PSB_PAD_RIGHT))     //boton derecha   
        {
          #ifdef debug
          Serial.println("Derecha");
          #endif   
          variable_control=14;  
          return;    
        }

        if(ps2x.ButtonPressed(PSB_L1))
        {
          #ifdef debug
          Serial.println("L1");
          #endif
          variable_control=23;
          return; 
        }
         
         
        if(ps2x.ButtonPressed(PSB_R1))
        {
          #ifdef debug
          Serial.println("R1");
          #endif
          variable_control=24;
          return; 
        }


//------------------------------------Lectura de Los analogicos-------------------------------------------------   
   /*
      #ifdef debug

        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC);

      #endif
        
     if(ps2x.Analog(PSS_LY)>(128+margen_joystick))   //me fijo si joystick Izquierdo para abajo
     {
     variable_control=17;
     return; 
     }
     if(ps2x.Analog(PSS_LY)<(128-margen_joystick))   //me fijo si joystick Izquierdo para arriba
     {
     variable_control=18;
     return; 
     }
     if(ps2x.Analog(PSS_LX)>(128+margen_joystick))   //me fijo si joystick Izquierdo para derecha
     {
     variable_control=15;
     return; 
     }
     if(ps2x.Analog(PSS_LX)<(128-margen_joystick))  //me fijo si joystick Izquierdo para izquierda
     {
     variable_control=16;
     return; 
     }
     if(ps2x.Analog(PSS_RY)>(128+margen_joystick))  //me fijo si joystick derecho para abajo
     {
     variable_control=19;
     return; 
     }
     if(ps2x.Analog(PSS_RY)<(128-margen_joystick))  //me fijo si joystick derecho para arriba
     {
     variable_control=20;
     return; 
     }
     if(ps2x.Analog(PSS_RX)>(128+margen_joystick))  //me fijo si joystick derecho para derecha
     {
     variable_control=21;
     return; 
     }
     if(ps2x.Analog(PSS_RX)<(128-margen_joystick))  //me fijo si joystick derecho para izquierda
     {
     variable_control=22;
     return; 
     }

*/
}


//-------------------------------------------------------------------
//               FIN PROGRAMA
//-------------------------------------------------------------------


