/*
Cayenne Ethernet W5500 Example

This sketch connects to the Cayenne server using an Arduino Ethernet Shield W5500
and runs the main communication loop.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
If you already have an Ethernet2 library installed you can skip steps 1 and 2.
1. Download the Ethernet2 library (https://github.com/adafruit/Ethernet2) as a zip file.
2. From the Arduino IDE Include Library menu select Add .ZIP Library and add the downloaded Ethernet2 zip library.
3. Set the token variable to match the Arduino token from the Dashboard.
4. Compile and upload this sketch.

For Cayenne Dashboard widgets using digital or analog pins this sketch will automatically
send data on those pins to the Cayenne server. If the widgets use Virtual Pins, data
should be sent to those pins using virtualWrites. Examples for sending and receiving
Virtual Pin data are under the Basics folder.
*/

//#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneEthernetW5500.h>

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token);
}

void loop()
{
	Cayenne.run();
}
