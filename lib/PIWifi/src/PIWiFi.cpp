#include "PIWiFi.h"
#include <WiFi.h>
#include <PIWiFiHandler.h>

// WL_NO_SHIELD        = 255
// WL_IDLE_STATUS      = 0
// WL_NO_SSID_AVAIL    = 1
// WL_SCAN_COMPLETED   = 2
// WL_CONNECTED        = 3
// WL_CONNECT_FAILED   = 4
// WL_CONNECTION_LOST  = 5
// WL_DISCONNECTED     = 6

PIWiFi::PIWiFi(char *ssid, char *password, int waitTime)
{
  _lastInteraction = 0;
  _waitTime = waitTime;

  _wifiState = new PIWiFiState(ssid, password, false);

  setUpWiFi();
}

void PIWiFi::setUpWiFi()
{
  WiFi.mode(WIFI_STA);
}

void PIWiFi::loop()
{
  unsigned long timePass = millis() - _lastInteraction;

  if (timePass < _waitTime)
  {
    return;
  }

  int wifiStatus = WiFi.status();

  if (wifiStatus == WL_IDLE_STATUS || wifiStatus == WL_DISCONNECTED)
    PIWIFI_IDLE_HANDLER(_wifiState);

  if (wifiStatus == WL_CONNECTED)
    PIWIFI_CONNECTED_HANDLER(_wifiState);

  _lastInteraction = millis();
}
