#include <LiquidCrystal.h> //Biblioteca do LCD 
#include <BME280.h> // Biblioteca do Sensor
#include <Wire.h> // Biblioteca I2C

#define SERIAL_BAUD 115200

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
BME280 bme;

void printBME280Data(Stream * client);
void printBME280CalculatedData(Stream* client);

 
void setup(){
  lcd.begin(16, 2); //Inicia o LCD com dimensões 16x2(Colunas x Linhas)
  lcd.setCursor(0, 0); //Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
  lcd.print("Inicializando!"); //Escreve no LCD "Olá Garagista!"
  while(!bme.begin()){
    lcd.setCursor(0, 0); //Posiciona o cursor na primeira coluna(0) e na primeira linha(0) do LCD
    lcd.print("ERRO NO SENSOR!"); //Escreve no LCD "Olá Garagista!"
  }

  //lcd.setCursor(0, 1); //Posiciona o cursor na primeira coluna(0) e na segunda linha(1) do LCD
  //lcd.print("LabdeGaragem"); //Escreve no LCD "LabdeGaragem"
 
}
 
void loop()
{
  for(int i = 0; i<2; i++){
    lcd.setCursor(0, i); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
    lcd.print("                ");
  }
  
  float temp(NAN), hum(NAN), pres(NAN);
  uint8_t pressureUnit(3);                                           // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi
  bme.ReadData(pres, temp, hum, true, pressureUnit);                // Parameters: (float& pressure, float& temp, float& humidity, bool celsius = false, uint8_t pressureUnit = 0x0)
  float altitude = bme.CalculateAltitude(true); //True = Sistema Metrico
  lcd.setCursor(0, 0); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print("Temp: ");
  lcd.setCursor(6, 0); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print(temp);
  lcd.setCursor(15, 0); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print("C");
  
  lcd.setCursor(0, 1); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print("Alti: ");
  lcd.setCursor(6, 1); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print(altitude);
  lcd.setCursor(15, 1); //Posiciona o cursor na décima quarta coluna(13) e na segunda linha(1) do LCD
  lcd.print("m");
  delay(1000);
}
