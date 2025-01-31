#include <Inkplate.h>
#include "WiFiHelper.h"

#define BAUD_RATE 115200
#define WIFI_SSID "D-Link-2.4G"
#define WIFI_PASSWORD "51543BED9AD4344C156A"

Inkplate display;
WiFiHelper wifiHelper(WIFI_SSID, WIFI_PASSWORD);

void setup()
{
	Serial.begin(BAUD_RATE);

	// Initialize display
	display.begin();
	display.clearDisplay();
	display.setTextColor(INKPLATE2_BLACK);

	// Attempt WiFi connection
	Serial.println("Connecting to WiFi...");
	if(wifiHelper.connect())
	{
		Serial.println("WiFi connected successfully");
		wifiHelper.setTime();
	} else
	{
		Serial.println("WiFi connection failed");
	}
}

void loop()
{
	// Attempt reconnection if disconnected
	if(!wifiHelper.isConnected())
	{
		Serial.println("WiFi disconnected, attempting reconnection...");
		if(!wifiHelper.connect())
		{
			delay(5000);  // Wait before retrying
			return;
		}
	}

	wifiHelper.updateDisplay(display);
}
