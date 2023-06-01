#ifndef PI_MQTT_H
#define PI_MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

class PIMQTTHandler
{
public:
  PIMQTTHandler(){};

  virtual void handle(String message) = 0;
};

class PIMQTT
{
private:
  int _waitTime = 500;
  unsigned long _lastInteraction;
  char *_clientId;
  WiFiClient _wifiClient;

public:
  PIMQTT(char *serverIP, char *clientId, int mqttPort);
  void setUpMQTT(char *serverIP, int mqttPort);

  PubSubClient *_mqttClient;

  void loop();
};

#endif
