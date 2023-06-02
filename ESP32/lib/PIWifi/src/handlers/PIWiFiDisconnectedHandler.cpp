
#include <PIWiFiHandler.h>
#include <WiFi.h>

void PIWIFI_DISCONNECTED_HANDLER(PIWiFiState *wifiState)
{
  if (wifiState->_isConnecting)
  {
    return;
  }

  wifiState->_isConnecting = true;
  WiFi.begin(wifiState->_ssid, wifiState->_password);
}
