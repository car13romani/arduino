# Cayenne ESP8266 WiFi Example

This sketch connects to the Cayenne server using a standalone ESP8266 WiFi module
and runs the main communication loop.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
1. Make sure the ESP8266 Board Package for your board is installed. For instructions see https://github.com/esp8266/Arduino.
2. Select your ESP8266 board from the Arduino IDE Board Manager.
3. Set the token variable to match the Arduino token from the Dashboard.
4. Set the network name and password.
5. Compile and upload this sketch.

For Cayenne Dashboard widgets using digital or analog pins this sketch will automatically
send data on those pins to the Cayenne server. If the widgets use Virtual Channels, data
should be sent to those channels using virtualWrites. Examples for sending and receiving
Virtual Pin data are under the Basics folder.
*/