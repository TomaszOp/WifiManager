#include <Arduino.h>

#include "WifiManager/WifiManager.h"

WifiManager wifiManager;

const char* _ssid ="sid";
const char* _password = "password";

void setup() {
  wifiManager.TryInitWifi(_ssid, _password); 
}

void loop() {
  
}

