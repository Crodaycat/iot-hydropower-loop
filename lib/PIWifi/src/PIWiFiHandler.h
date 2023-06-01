#ifndef PIWIFI_HANDLER_H
#define PIWIFI_HANDLER_H
#include <PIWiFiState.h>

void PIWIFI_IDLE_HANDLER(PIWiFiState *wifiState);
void PIWIFI_DISCONNECTED_HANDLER(PIWiFiState *wifiState);
void PIWIFI_CONNECTED_HANDLER(PIWiFiState *wifiState);

#endif
