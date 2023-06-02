#include <PIMQTT.h>
// #include <PIMQTTHandler.h>

// MQTT_CONNECTION_TIMEOUT     -4
// MQTT_CONNECTION_LOST        -3
// MQTT_CONNECT_FAILED         -2
// MQTT_DISCONNECTED           -1
// MQTT_CONNECTED               0
// MQTT_CONNECT_BAD_PROTOCOL    1
// MQTT_CONNECT_BAD_CLIENT_ID   2
// MQTT_CONNECT_UNAVAILABLE     3
// MQTT_CONNECT_BAD_CREDENTIALS 4
// MQTT_CONNECT_UNAUTHORIZED    5

PIMQTT::PIMQTT(char *serverIP, char *clientId, int mqttPort)
{
  _lastInteraction = 0;
  _clientId = clientId;

  setUpMQTT(serverIP, mqttPort);
}

void PIMQTT::setUpMQTT(char *serverIP, int mqttPort)
{
  _mqttClient = new PubSubClient();

  _mqttClient->setServer(serverIP, mqttPort);
  _mqttClient->setClient(_wifiClient);
}

void PIMQTT::loop()
{
  unsigned long timePass = millis() - _lastInteraction;

  if (timePass < _waitTime)
  {
    return;
  }

  int clientState = _mqttClient->state();
  int wifiStatus = WiFi.status();

  if (wifiStatus != WL_CONNECTED)
  {
    _lastInteraction = millis();
    return;
  }

  if (clientState != MQTT_CONNECTED)
  {
    Serial.println("MQTT Start connection");

    if (_mqttClient->connect(_clientId))
    {
      Serial.println("connected");

      _mqttClient->subscribe("hydro/raspberry");
    }
    else
    {
      Serial.print("failed connection, rc = ");
      Serial.println(_mqttClient->state());
      Serial.println("Trying again in a moment");
    }
  }

  if (clientState == MQTT_CONNECTED)
  {
    _mqttClient->loop();
  }

  _lastInteraction = millis();
}
