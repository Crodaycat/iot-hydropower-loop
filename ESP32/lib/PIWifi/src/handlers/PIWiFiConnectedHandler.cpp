
#include <PIWiFiHandler.h>
#include <WiFi.h>

void PIWIFI_CONNECTED_HANDLER(PIWiFiState *wifiState)
{
  if (!wifiState->_isConnecting)
  {
    return;
  }

  wifiState->_isConnecting = false;

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
