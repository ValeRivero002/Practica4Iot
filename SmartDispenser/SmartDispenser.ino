#include <Arduino.h>
#include "WeightSensor.h"
#include "ServoActuator.h"
#include "Dispenser.h"
#include "CommunicationManager.h"
#include "MQTTManager.h"
#include "certificates.h"

// Configuración de pines y conexión
#define SERVO_PIN           26
#define LOADCELL_DOUT_PIN   25
#define LOADCELL_SCK_PIN    33

#define WIFI_SSID   "C21 URBAN"
#define WIFI_PASS   "AAV29JPI05"
#define BROKER_URL  "a2dbaocrje4klj-ats.iot.us-east-2.amazonaws.com"
#define MQTT_PORT   8883
#define CLIENT_ID   "ESP32-SMART-DISPENSER-001"

// Instancias de clases
WeightSensor        sensor(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
ServoActuator       servo(SERVO_PIN);
Dispenser           dispenser(&servo, &sensor);
CommunicationManager comm(WIFI_SSID, WIFI_PASS, AMAZON_ROOT_CA1, CERTIFICATE, PRIVATE_KEY);
MQTTManager         mqtt(BROKER_URL, MQTT_PORT, CLIENT_ID);

// Variables de estado anterior
String previousClass = "";
String previousState = "";

void setup() {
  Serial.begin(115200);
  dispenser.begin();
  comm.connectWiFi();
  mqtt.begin(comm, &dispenser);
}

void loop() {
  mqtt.loop();

  static unsigned long lastRead = 0;
  if (millis() - lastRead >= 500) {
    lastRead = millis();

    float peso = dispenser.readWeight();
    String currentClass = dispenser.classifyWeight(peso);
    String currentState = dispenser.getCurrentState();

    Serial.printf("Peso: %.1f g → %s | Estado: %s\n", peso, currentClass.c_str(), currentState.c_str());

    // Publicar solo si hay cambio en la clasificación o en el estado
    if (currentClass != previousClass || currentState != previousState) {
      previousClass = currentClass;
      previousState = currentState;
      mqtt.reportShadow();
    }
  }
}
