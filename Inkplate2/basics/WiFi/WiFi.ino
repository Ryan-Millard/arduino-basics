#include <Inkplate.h>
#include "WiFiHelper.h"
#define BAUD_RATE 115200
#define WIFI_SSID "D-Link-2.4G"
#define WIFI_PASSWORD "51543BED9AD4344C156A"
#define UPDATE_INTERVAL 60000  // 60 seconds in milliseconds

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
	if(!wifiHelper.connect())
	{
		Serial.println("WiFi connection failed");
		return;
	}
	Serial.println("WiFi connected successfully");
	wifiHelper.setTime();
}

void loop()
{
	static unsigned long lastUpdate = 0;

	// Check if it's time for an update
	if(millis() - lastUpdate >= UPDATE_INTERVAL)
	{
		if(!wifiHelper.isConnected())
		{
			Serial.println("WiFi disconnected, attempting reconnection...");
			wifiHelper.connect();
		}

		wifiHelper.updateDisplay(display);
		lastUpdate = currentMillis;
	}
}
