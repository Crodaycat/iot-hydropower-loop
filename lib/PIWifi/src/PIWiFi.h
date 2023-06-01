#ifndef PI_WIFI_H
#define PI_WIFI_H
#include <Arduino.h>
#include <PIWiFiState.h>

class PIWiFi
{
private:
  int _waitTime = 500;
  unsigned long _lastInteraction;
  PIWiFiState *_wifiState;

  void setUpWiFi();

public:
  PIWiFi(char *ssid, char *password, int waitTime);

  void loop();
};

#endif
