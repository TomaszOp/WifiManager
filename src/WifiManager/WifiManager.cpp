#include "Arduino.h"

#include "WifiManager.h"

	WifiManager::WifiManager()
	{
		this->uartSpeed= DEFAULT_UartSpeed; 
		this->Mode = MODE_NOT_SET;
	}

	WifiManager::~WifiManager() 
	{

	}

	void WifiManager::SetUartSpeed(int _value)
	{
		Serial.begin(_value);
	}

	void WifiManager::InitWifi(const char* _ssid, const char* _password)
	{
		Serial.begin(this->uartSpeed);

		WiFi.mode(WIFI_STA);
		WiFi.begin(_ssid, _password);
		Serial.println("");

		// Wait for connection
		while (WiFi.status() != WL_CONNECTED) 
		{
		delay(500);
		Serial.print(".");
		}

		Serial.println("");
		Serial.print("Connected to ");
		Serial.println(_ssid);
		Serial.print("IP address: ");
		Serial.println(WiFi.localIP());

		this->Mode = MODE_WIFI_STA;
	}

	void WifiManager::TryInitWifi(const char* _ssid, const char* _password)
	{
		Serial.begin(this->uartSpeed);

		WiFi.mode(WIFI_STA);
		WiFi.begin(_ssid, _password);
		Serial.println("");

		int i = 0;
		while (WiFi.status() != WL_CONNECTED && i <= 15) 
		{
		delay(500);
		Serial.print(".");
		i++;
		}

		if(i == 15)
		{
		WiFi.mode(WIFI_AP);
		delay(100);

		IPAddress localIp(192,168,1,1);
		IPAddress gateway(192,168,1,1);
		IPAddress subnet(255,255,255,0);

		WiFi.softAPConfig(localIp, gateway, subnet);
		WiFi.softAP(_ssid);

		IPAddress IP = WiFi.softAPIP();

		WiFi.softAPIP();
		Serial.print("AP IP address: ");
		Serial.println(IP);

		this->Mode = MODE_WIFI_AP;
	}   
	else
	{
		Serial.println("");
		Serial.print("IP address: ");

		IPAddress IP = WiFi.localIP();
		Serial.println(IP);

		this->Mode = MODE_WIFI_STA;
		}
	}

	void WifiManager::InitWifiAP(const char* _ssid)
	{
		Serial.begin(this->uartSpeed);

		WiFi.mode(WIFI_AP);
		delay(100);

		IPAddress localIp(192,168,1,1);
		IPAddress gateway(192,168,1,1);
		IPAddress subnet(255,255,255,0);

		WiFi.softAPConfig(localIp, gateway, subnet);
		WiFi.softAP(_ssid);

		//Serial.print("IP address: ");
		//Serial.println(WiFi.localIP());

		IPAddress IP = WiFi.softAPIP();
		Serial.print("AP IP address: ");
		Serial.println(IP);

		this->Mode = MODE_WIFI_AP;
	}

	IPAddress WifiManager::GetIPAddress()
	{
		if(this->Mode == MODE_WIFI_STA)
		{
		return WiFi.localIP();
		}
		else if(this->Mode == MODE_WIFI_AP)
		{
		return WiFi.softAPIP();
		}

		return WiFi.localIP();
	}

	void WifiManager::Disconnect()
	{
		WiFi.disconnect();
	}
