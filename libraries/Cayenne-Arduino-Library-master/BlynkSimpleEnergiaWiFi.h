/**
 * @file       BlynkSimpleEnergiaWiFi.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 *
 * Modified May 2016 by myDevices.
 */

#ifndef BlynkSimpleEnergiaWiFi_h
#define BlynkSimpleEnergiaWiFi_h

#include <WiFi.h>
#include <Adapters/BlynkWiFiCommon.h>

//Initialize the socket to 255 to prevent issues when disconnect is called before connect, as is done by Blynk.
static WiFiClient _blynkWifiClient(255);
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);
BlynkWifiCommon Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
