# Cayenne Ethernet W5200 Example

This sketch connects to the Cayenne server using an Arduino Ethernet Shield W5200
and runs the main communication loop.

The Cayenne Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

###### Steps:
###### If you already have the Ethernet_Shield_W5200 library installed you can skip steps 1 and 2.
1. Download the Ethernet_Shield_W5200 library (https://github.com/Seeed-Studio/Ethernet_Shield_W5200) as a zip file.
2. From the Arduino IDE Include Library menu select Add .ZIP Library and add the downloaded Ethernet_Shield_W5200 zip library.
3. Set the token variable to match the Arduino token from the Dashboard.
4. Compile and upload this sketch.

For Cayenne Dashboard widgets using digital or analog pins this sketch will automatically
send data on those pins to the Cayenne server. If the widgets use Virtual Channels, data
should be sent to those channels using virtualWrites. Examples for sending and receiving
Virtual Pin data are under the Basics folder.