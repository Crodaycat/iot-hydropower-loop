#include <Arduino.h>
#include <PIWiFi.h>
#include <PIMQTT.h>

PIWiFi *wiFiController;
PIMQTT *mqttController;

#define ECHO_PIN_A 18    // Naranja
#define TRIGGER_PIN_A 19 // Verde
#define ECHO_PIN_B 12    // Naranja
#define TRIGGER_PIN_B 14 // Verde
#define TANK_A_PUMP_PIN 16
#define TANK_B_PUMP_PIN 17

int waterLevelA = 0, waterLevelB = 0;
String hydroGenOn = "ON";
unsigned long _lastInteraction = 0;

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("Message arrived [" + String(topic) + "]");

  String message;

  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  Serial.print("[MESSAGE]: ");
  Serial.println(message);

  String stringTopic = String(topic);

  if (stringTopic == "hydro/raspberry")
  {
    hydroGenOn = message;
  }
}

void setup()
{
  Serial.begin(9600);

  wiFiController = new PIWiFi("Luis", "h3110w0r1d", 500);
  mqttController = new PIMQTT("192.168.43.129", "PumpsClient", 1883);
  mqttController->_mqttClient->setCallback(callback);

  pinMode(TRIGGER_PIN_A, OUTPUT);
  pinMode(ECHO_PIN_A, INPUT);
  pinMode(TRIGGER_PIN_B, OUTPUT);
  pinMode(ECHO_PIN_B, INPUT);
  pinMode(TANK_A_PUMP_PIN, OUTPUT);
  pinMode(TANK_B_PUMP_PIN, OUTPUT);
}

void updateWaterLevel()
{
  digitalWrite(TRIGGER_PIN_A, LOW);
  delayMicroseconds(4);

  digitalWrite(TRIGGER_PIN_A, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER_PIN_A, LOW);

  int durationA = pulseIn(ECHO_PIN_A, HIGH);

  waterLevelA = durationA * 100 / 292 / 2;

  digitalWrite(TRIGGER_PIN_B, LOW);
  delayMicroseconds(4);

  digitalWrite(TRIGGER_PIN_B, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER_PIN_B, LOW);

  int durationB = pulseIn(ECHO_PIN_B, HIGH);

  waterLevelB = durationB * 100 / 292 / 2;

  delay(500);

  // Maximo llenado 6.5CM
  // Mínimo 10CM

  // Grande
  // Minimo 16 CM Se detiene bomba
  // Maximo 6.5 CM // Maximo Arrancar bomba
}

void updatePumps()
{
  if (hydroGenOn != "ON")
  {
    digitalWrite(TANK_A_PUMP_PIN, LOW);
    digitalWrite(TANK_B_PUMP_PIN, LOW);
    return;
  }

  digitalWrite(TANK_A_PUMP_PIN, waterLevelA <= 156 && waterLevelB >= 50);
  digitalWrite(TANK_B_PUMP_PIN, waterLevelB <= 140 && waterLevelA >= 65);
}

void publishStatus()
{
  unsigned long timePass = millis() - _lastInteraction;

  if (timePass < 2000)
  {
    return;
  }

  _lastInteraction = millis();

  char message[32];
  snprintf(message, sizeof(message), "%i,%i,%s", waterLevelA, waterLevelB, hydroGenOn);

  Serial.println(message);

  mqttController->_mqttClient->publish("hydro/esp", message);
}

void loop()
{
  wiFiController->loop();
  mqttController->loop();
  updateWaterLevel();
  updatePumps();
  publishStatus();
}
