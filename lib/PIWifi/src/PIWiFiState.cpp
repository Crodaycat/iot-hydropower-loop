
#include <PIWiFiState.h>

PIWiFiState::PIWiFiState(char *ssid, char *password, boolean isConnecting)
{
  _ssid = ssid;
  _password = password;
  _isConnecting = isConnecting;
}
