// Test code for Adafruit GPS modules using MTK driver
// such as www.adafruit.com/products/660
// Pick one up today at the Adafruit electronics shop 
// and help support open source hardware & software! -ada

  //#if (ARDUINO >= 100)
//#include <SoftSerial.h>
//SoftSerial Serial2(2, 3);
 // #else
// If you're using Arduino IDE v23 or earlier, you'll
// need to install NewSoftSerial
//#include <NewSoftSerial.h>
//NewSoftSerial Serial2(2, 3);
 // #endif

// Connect the GPS Power pin to 3.3V
// Connect the GPS Ground pin to ground
// Connect the GPS VBAT pin to 3.3V if no battery is used
// Connect the GPS TX (transmit) pin to Digital 2
// Connect the GPS RX (receive) pin to Digital 3
// For 3.3V only modules such as the UP501, connect a 10K
// resistor between digital 3 and GPS RX and a 10K resistor 
// from GPS RX to ground.

// different commands to set the update rate from once a second (1 Hz) to 10 times a second (10Hz)
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"

// turn on only the second sentence (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
// turn on ALL THE DATA
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

// to generate your own sentences, check out the MTK command datasheet and use a checksum calculator
// such as the awesome http://www.hhhh.org/wiml/proj/nmeaxor.html

void setup()  
{
  Serial.begin(57600);
  Serial.println("Adafruit MTK3329 NMEA test!");

  // 9600 NMEA is the default baud rate
  Serial2.begin(9600);
  
  // uncomment this line to turn on only the "minimum recommended" data for high update rates!
  //Serial2.println(PMTK_SET_NMEA_OUTPUT_RMCONLY);

  // uncomment this line to turn on all the available data - for 9600 baud you'll want 1 Hz rate
  Serial2.println(PMTK_SET_NMEA_OUTPUT_ALLDATA);
  
  // Set the update rate
  // 1 Hz update rate
  Serial2.println(PMTK_SET_NMEA_UPDATE_1HZ);
  // 5 Hz update rate- for 9600 baud you'll have to set the output to RMC only (see above)
  //Serial2.println(PMTK_SET_NMEA_UPDATE_5HZ);
  // 10 Hz update rate - for 9600 baud you'll have to set the output to RMC only (see above)
  //Serial2.println(PMTK_SET_NMEA_UPDATE_10HZ);

}

void loop()                     // run over and over again
{

  if (Serial2.available()) {
      Serial.print((char)Serial2.read());
  }
  if (Serial.available()) {
      Serial2.print((char)Serial.read());
  }
}
