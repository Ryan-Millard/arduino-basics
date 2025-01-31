#include "WiFiHelper.h"
#include <time.h>

WiFiHelper::WiFiHelper(const char* ssid, const char* password)
	: _ssid(ssid), _password(password), _lastDisplayUpdate(0) {}

bool WiFiHelper::connect()
{
	if(isConnected())
	{
		return true;
	}

	WiFi.begin(_ssid, _password);
	const unsigned long startAttemptTime = millis();

	while(!isConnected() && (millis() - startAttemptTime <= WIFI_TIMEOUT_MS))
	{
		delay(500);
	}

	return isConnected();
}

bool WiFiHelper::setTime()
{
	if(!isConnected())
	{
		return false;
	}

	configTime(2 * 3600, 0, "pool.ntp.org");
	struct tm timeinfo;
	return getLocalTime(&timeinfo);
}

String WiFiHelper::getTimeString() const
{
	struct tm timeinfo;
	if(!getLocalTime(&timeinfo))
	{
		return "Time sync failed";
	}

	char timeString[50];
	strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);
	return String(timeString);
}

String WiFiHelper::getLocalIP() const
{
	return isConnected() ? WiFi.localIP().toString() : "Not Connected";
}

bool WiFiHelper::isConnected() const
{
	return WiFi.status() == WL_CONNECTED;
}

String WiFiHelper::getRSSI() const
{
	return isConnected() ? String(WiFi.RSSI()) : "N/A";
}

void WiFiHelper::displayConnectionStatus(Inkplate& display, const String& message) const
{
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(10, 10);
	display.println(message);
	if(isConnected())
	{
		display.println("IP: " + getLocalIP());
	}
	display.display();
}

void WiFiHelper::updateDisplay(Inkplate& display)
{
	unsigned long currentMillis = millis();
	if(currentMillis - _lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL_MS)
	{
		display.clearDisplay();

		// Display time in larger text
		display.setTextSize(2);
		display.setCursor(10, 30);
		display.print("Time: ");
		display.println(getTimeString());

		// Display network info in smaller text
		display.setTextSize(1);
		display.setCursor(10, 60);
		display.println("WiFi RSSI: " + getRSSI() + " dBm");
		display.println("Local IP: " + getLocalIP());

		display.display();
		_lastDisplayUpdate = currentMillis;
	}
}
