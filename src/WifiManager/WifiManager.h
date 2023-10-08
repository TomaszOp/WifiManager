#ifndef _WifiManager_H_
#define _WifiManager_H_

#include <Arduino.h>

//#include <ESP8266WiFi.h>
#include <WiFi.h>

#define DEFAULT_UartSpeed 115200

#define MODE_NOT_SET  0
#define MODE_WIFI_STA 1
#define MODE_WIFI_AP  2

class WifiManager
{
	public:
	WifiManager();
	~WifiManager();
				 
	void SetUartSpeed(int _value);

	void InitWifi(const char* _ssid, const char* _password);
	void InitWifiAP(const char* _ssid);
	void TryInitWifi(const char* _ssid, const char* _password);

	IPAddress GetIPAddress();
	int8_t Mode;

	void Disconnect();

	private: 
	
	int uartSpeed;  
}; 

#endif
