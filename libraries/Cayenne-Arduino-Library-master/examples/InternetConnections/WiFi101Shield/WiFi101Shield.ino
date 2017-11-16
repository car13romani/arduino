/*
Cayenne WiFi Shield 101 Example

This sketch connects to the Cayenne server using an Arduino WiFi Shield 101
and runs the main communication loop.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Install the WiFi101 library (https://github.com/arduino-libraries/WiFi101) from the Arduino Library Manager if you have not done so already.
2. Set the token variable to match the Arduino token from the Dashboard.
3. Set the network name and password.
4. Compile and upload this sketch.

For Cayenne Dashboard widgets using digital or analog pins this sketch will automatically
send data on those pins to the Cayenne server. If the widgets use Virtual Pins, data
should be sent to those pins using virtualWrites. Examples for sending and receiving
Virtual Pin data are under the Basics folder.
*/

//#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneWiFi101.h>

// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = "AuthenticationToken";
// Your network name and password.
char ssid[] = "NetworkSSID";
char password[] = "NetworkPassword";

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(token, ssid, password);
}

void loop()
{
	Cayenne.run();
}
