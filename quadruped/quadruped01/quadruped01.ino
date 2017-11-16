#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <NewPing.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 400
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

//-------------------------------------------------------------------
//Con este timer se setea la velocidad de movimiento de todo el robot, mas chico, mas rapido
//-------------------------------------------------------------------

int Time=150;

//-------------------------------------------------------------------
//  Definicion de las constantes posicion inicial de cada servo
//-------------------------------------------------------------------

//subir = giro antihor en cuerpo y patas

#define FIC_centro      220     //Frente_Izquierda_cuerpo_centro
#define FDC_centro      300     //Frente_derecha_cuerpo_centro
#define AIC_centro      270     //Atras_Izquierda_cuerpo_centro
#define ADC_centro      180     //Atras_derecha_cuerpo_centro

#define FIP_centro      340      //Frente_Izquierda_pata_centro
#define FDP_centro      100      //Frente_derecha_pata_centro
#define AIP_centro      200      //Atras_Izquierda_pata_centro
#define ADP_centro      150      //Atras_derecha_pata_centro

//-------------------------------------------------------------------
//      Definicion Alias de cada servo y los Pines del Arduino
//-------------------------------------------------------------------

#define FIC_servo 14                                               // Front Left  Hip
#define FDC_servo 13                                             // Front Right Hip
#define AIC_servo 2                                              // Rear  Left  Hip
#define ADC_servo 1                                              // Rear  Right Hip
#define FIP_servo 15                                             // Front Left  Knee
#define FDP_servo 12                                               // Front Right Knee
#define AIP_servo 3                                               // Rear  left  Knee
#define ADP_servo 0                                               // Rear  Right Knee


#define pulsador_arranque 12  //defino donde va conectado el pulsador de arranque


//-------------------------------------------------------------------

int movimiento_izq;
int movimiento_der;
int levanta=-100;

int contador_sentarse;
int distancia_actual = 0;
int pos = 90;

int max_der = 0;
int max_izq = 0;
int aux=0;    //auxiliar que utilizo para las funciones especiales
int variable_sienta=200;

const int tiempo_entre_servo=5;
const int tiempo_sienta=50;

int variable_control=0;   //variable que indica que comando fue pulsado en el PS2


void setup()
{
  
  //-------------------------------------------------------------------
  // Inicializo Los servos con los nombres y cual es su pin asociado
  //-------------------------------------------------------------------

 #ifdef debug
   Serial.begin(57600);
 #endif
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();


//-------------------------------------------------------------------
//         Arranco Todos los Servos en sus posiciones iniciales
//-------------------------------------------------------------------

  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(tiempo_entre_servo);
  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(tiempo_entre_servo); 
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(tiempo_entre_servo);
  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(tiempo_entre_servo);
  pwm.setPWM(FIP_servo, 0, FIP_centro);
  delay(tiempo_entre_servo);
  pwm.setPWM(FDP_servo, 0, FDP_centro);
  delay(tiempo_entre_servo);
  pwm.setPWM(AIP_servo, 0, AIP_centro);
  delay(tiempo_entre_servo);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(tiempo_entre_servo);

delay(500);  
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}










//-------------------------------------------------------------------
//         Sector donde comienza la funcion Principal,
//        Donde se va a quedar el resto de la ejecucion
//-------------------------------------------------------------------
  
void loop()
{
  
  while(1)   //se queda en este loop luego de haber pulsado el pulsador de arranque
  {

    lectura_control();


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
          angelito_levanta();
          aux=0;
          delay(300);
        }

//-------------------comandos de movimientos normales--------------------
        
    if(variable_control=='1')  //fue pulsado arriba
    {
       movimiento_izq=-100;
      movimiento_der=-100;
      Camina_frente();
    }
    if(variable_control=='2')  //fue pulsado abajo
    {
      camina_atras();
    }
    if(variable_control=='3') //fue pulsado izquierda
    {
      Gira_der() ; 
    }
    if(variable_control=='4')  //fue pulsado derecha
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
  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(tiempo);
  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(tiempo);
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(tiempo);
  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(tiempo);
  pwm.setPWM(FIP_servo, 0, FIP_centro);
  delay(tiempo);
  pwm.setPWM(FDP_servo, 0, FDP_centro);
  delay(tiempo);
  pwm.setPWM(AIP_servo, 0, AIP_centro);
  delay(tiempo);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(tiempo);
}

//-------------------------------------------------------------------
//             Funcion Avanzar hacia el frente
//-------------------------------------------------------------------
void Camina_frente()
{

  pwm.setPWM(FDP_servo, 0, FDP_centro-levanta);             // raise front right leg 
  delay(tiempo_entre_servo);
  pwm.setPWM(AIP_servo, 0, AIP_centro-levanta);                // raise rear  left  leg
  delay(tiempo_entre_servo);
  pwm.setPWM(FIC_servo, 0, FIC_centro-movimiento_izq);         // move  front left  leg backward
  delay(tiempo_entre_servo);
  pwm.setPWM(ADC_servo, 0, ADC_centro+movimiento_der);         // move  rear  right leg backward
  delay(Time/2);
  pwm.setPWM(FDC_servo, 0, FDC_centro-movimiento_der);         // move  front right leg forward
  delay(tiempo_entre_servo);
  pwm.setPWM(AIC_servo, 0, AIC_centro+movimiento_izq);         // move  rear  left  leg forward
  delay(Time);
  pwm.setPWM(FDP_servo, 0, FDP_centro);                        // lower front right leg 
  delay(tiempo_entre_servo);
  pwm.setPWM(AIP_servo, 0, AIP_centro);                       // lower rear  left  leg
  delay(Time);
    
  pwm.setPWM(FIP_servo, 0, FIP_centro-levanta);                // raise front left  leg
  delay(tiempo_entre_servo);
  pwm.setPWM(ADP_servo, 0, ADP_centro-levanta);                // raise rear  right leg
  delay(tiempo_entre_servo);
  pwm.setPWM(FDC_servo, 0, FDC_centro+movimiento_der);         // move  front right leg backward
  delay(tiempo_entre_servo);
  pwm.setPWM(AIC_servo, 0, AIC_centro-movimiento_izq);         // move  rear  left  leg backward
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro+movimiento_izq);         // move  front left  leg forward
  delay(tiempo_entre_servo);
  pwm.setPWM(ADC_servo, 0, ADC_centro-movimiento_der);         // move  rear  right leg forward
  delay(Time);
  pwm.setPWM(FIP_servo, 0, FIP_centro);                        // lower front left  leg
  delay(tiempo_entre_servo);
  pwm.setPWM(ADP_servo, 0, ADP_centro);                        // lower rear  right leg
  delay(Time);  

  }

    
//-------------------------------------------------------------------
//                 Gira Derecha
//-------------------------------------------------------------------


void Gira_der() 
{
   movimiento_izq=200;
   movimiento_der=-200;
   Camina_frente();
}  

//-------------------------------------------------------------------
//                 Gira Izquierda
//-------------------------------------------------------------------

void Gira_izq() 
{
   movimiento_izq=-200;
   movimiento_der=200;
  Camina_frente();
}  

//-------------------------------------------------------------------
//               Camina hacia atras
//-------------------------------------------------------------------

void camina_atras()
{
   movimiento_izq=200;
   movimiento_der=200;
   Camina_frente();
}

//#####################################


//-------------------------------------------------------------------
//                  Funcion Sentarse
//-------------------------------------------------------------------
void sienta(void)
{
  pwm.setPWM(FDC_servo, 0, FDC_centro);             // raise front right leg 
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro);         // move  front left  leg backward
  delay(Time/2);  

  pwm.setPWM(ADC_servo, 0, ADC_centro+variable_sienta/3);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro-variable_sienta/3);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro+variable_sienta/3); 
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta/3);   
  delay(Time/2);
  
  pwm.setPWM(ADC_servo, 0, ADC_centro+variable_sienta/2);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro-variable_sienta/2);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro+variable_sienta/2); 
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta/2);   
  delay(Time/2);

  pwm.setPWM(ADC_servo, 0, ADC_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro-variable_sienta);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro+variable_sienta); 
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta);   
  delay(Time/2);

  delay(10);               
}  


void sentado_levanta(void)
{

  pwm.setPWM(FIP_servo, 0, FIP_centro);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, FDP_centro);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(Time/2);
  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(Time/2);
  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(Time/2);
  
  delay(10);
}


//-------------------------------------------------------------------
//                  Funcion Saluda
//-------------------------------------------------------------------

void saluda(void)
{

  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(Time/2);
  pwm.setPWM(ADC_servo, 0, ADC_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro-variable_sienta);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, 400);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta/3);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta/2);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta);
  delay(Time/2);
  
  delay(10);
}  

void saluda_levanta(void)
{
  
  pwm.setPWM(FIP_servo, 0, FIP_centro);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, FDP_centro);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(Time/2);
  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(Time/2);
  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(Time/2);
  
  delay(10);
}

//-------------------------------------------------------------------
//                  Funcion Mueve Pata en Frente
//-------------------------------------------------------------------

void mueve_pata_frente(void)
{
  int maximo=200;
    for(int j=0;j<maximo;j=j+100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro+j);
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro+j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=0;j<maximo;j=j+100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro-j);  //se tira al piso de costado
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro-j);
  delay(Time/2);
  }
}


//-------------------------------------------------------------------
//                  Funcion Alaba y se queda abajo
//-------------------------------------------------------------------
void alaba(void)
{

  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(Time/2);
  pwm.setPWM(FDC_servo, 0, FDC_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro-variable_sienta);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, FDP_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(FIP_servo, 0, FIP_centro+variable_sienta);
  delay(Time/2);  
  
  delay(10);               
}  


void alaba_levanta(void)
{
  
  pwm.setPWM(FIP_servo, 0, FIP_centro);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, FDP_centro);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(Time/2);
  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(Time/2);
  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(Time/2);
  
  delay(10);
}

//-------------------------------------------------------------------
//                  Funcion angelito
//-------------------------------------------------------------------
void angelito_cae(void)
{

  pwm.setPWM(FDC_servo, 0, FDC_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro-variable_sienta);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, FDP_centro+variable_sienta);
  delay(Time/2);  
  pwm.setPWM(FIP_servo, 0, FIP_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(ADC_servo, 0, ADC_centro-variable_sienta);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro+variable_sienta);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro+variable_sienta);
  delay(Time/2);  
  pwm.setPWM(AIP_servo, 0, AIP_centro+variable_sienta);
  delay(Time/2);

}

void angelito_levanta(void)
{
  
  pwm.setPWM(FIP_servo, 0, FIP_centro);
  delay(Time/2);
  pwm.setPWM(FDP_servo, 0, FDP_centro);
  delay(Time/2);
  pwm.setPWM(FIC_servo, 0, FIC_centro);
  delay(Time/2);
  pwm.setPWM(FDC_servo, 0, FDC_centro);
  delay(Time/2);
  pwm.setPWM(AIP_servo, 0, AIP_centro);
  delay(Time/2);
  pwm.setPWM(ADP_servo, 0, ADP_centro);
  delay(Time/2);
  pwm.setPWM(AIC_servo, 0, AIC_centro);
  delay(Time/2);
  pwm.setPWM(ADC_servo, 0, ADC_centro);
  delay(Time/2);
  
  delay(10);
}


void angelito_saluda(void)
{
    int maximo=600;
    for(int j=0;j<maximo;j=j+100)
  {

  pwm.setPWM(FDC_servo, 0, FDC_centro+j);
  pwm.setPWM(FIC_servo, 0, FDC_centro-j);
  pwm.setPWM(ADC_servo, 0, FDC_centro-j);
  pwm.setPWM(FIC_servo, 0, FDC_centro+j);
  
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro+j);
  pwm.setPWM(FIC_servo, 0, FDC_centro-j);
  pwm.setPWM(ADC_servo, 0, FDC_centro-j);
  pwm.setPWM(FIC_servo, 0, FDC_centro+j);

  
  delay(Time/2);
  }

  for(int j=0;j<maximo;j=j+100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro-j);
  pwm.setPWM(FIC_servo, 0, FDC_centro+j);
  pwm.setPWM(ADC_servo, 0, FDC_centro+j);
  pwm.setPWM(FIC_servo, 0, FDC_centro-j);
  delay(Time/2);
  }

  for(int j=maximo;j>0;j=j-100)
  {
  pwm.setPWM(FDC_servo, 0, FDC_centro-j);
  pwm.setPWM(FIC_servo, 0, FDC_centro+j);
  pwm.setPWM(ADC_servo, 0, FDC_centro+j);
  pwm.setPWM(FIC_servo, 0, FDC_centro-j);
  delay(Time/2);
  }
}



//-------------------------------------------------------------------------------------
void lectura_control(void)
{ 
        variable_control=Serial.read();
        if(variable_control < 0 and variable_control>30){
          variable_control = 0;
        }
        

}
