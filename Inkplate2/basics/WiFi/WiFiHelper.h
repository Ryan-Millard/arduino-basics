#ifndef WIFIHELPER_H
#define WIFIHELPER_H

#include <WiFi.h>

class WiFiHelper
{
	public:
		// Constants
		static constexpr unsigned long WIFI_TIMEOUT_MS = 10000;  // 10 seconds timeout
		static constexpr unsigned long DISPLAY_UPDATE_INTERVAL_MS = 1000; // 1 second refresh

		// Constructor
		WiFiHelper(const char* ssid, const char* password);

		// Public methods
		bool connect();
		bool setTime();
		String getLocalIP() const;
		bool isConnected() const;
		String getRSSI() const;
		void updateDisplay(Inkplate& display);

	private:
		// Private members
		const char* _ssid;
		const char* _password;
		unsigned long _lastDisplayUpdate;

		// Private methods
		void displayConnectionStatus(Inkplate& display, const String& message) const;
		String getTimeString() const;
};

#endif
