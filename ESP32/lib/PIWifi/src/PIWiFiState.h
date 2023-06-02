#ifndef PIWIFI_STATE_H
#define PIWIFI_STATE_H
#include <Arduino.h>

class PIWiFiState
{
public:
  boolean _isConnecting = false;
  char *_ssid;
  char *_password;

  PIWiFiState(char *ssid, char *password, boolean isConnecting);
};
#endif
