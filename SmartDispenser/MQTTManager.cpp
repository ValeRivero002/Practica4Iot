#include "MQTTManager.h"

MQTTManager* MQTTManager::instance = nullptr;

MQTTManager::MQTTManager(const char* broker, int port, const char* clientId)
  : broker(broker), port(port), clientId(clientId), client() {
  instance = this;
}

void MQTTManager::begin(CommunicationManager& comm, Dispenser* dispenser) {
  this->dispenser = dispenser;
  client.setClient(comm.getSecureClient());
  client.setServer(broker, port);
  client.setCallback(callbackStatic);
  reconnect();
}

void MQTTManager::loop() {
  if (!client.connected()) reconnect();
  client.loop();
}

void MQTTManager::reconnect() {
  while (!client.connected()) {
    if (client.connect(clientId)) {
      Serial.println("Conectado exitosamente a MQTT Broker");
      client.subscribe(DELTA_TOPIC);
      reportShadow();
    } else {
      Serial.print("Error de conexión MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" → Reintentando...");
      delay(500);
    }
  }
}

void MQTTManager::reportShadow() {
  outputDoc.clear();
  auto state = outputDoc.createNestedObject("state").createNestedObject("reported");
  state["weight"] = dispenser->classifyWeight(dispenser->readWeight());
  state["dispenser_state"] = dispenser->getCurrentState();
  serializeJson(outputDoc, outputBuffer);
  Serial.print("Reportando a shadow: ");
  Serial.println(outputBuffer);

  client.publish(UPDATE_TOPIC, outputBuffer);
}

void MQTTManager::callbackStatic(char* topic, byte* payload, unsigned int length) {
  if (instance) instance->callbackInternal(topic, payload, length);
}

void MQTTManager::callbackInternal(char* topic, byte* payload, unsigned int length) {
  Serial.print(" Mensaje recibido en tópico: ");
  Serial.println(topic);
  
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print(" Contenido: ");
  Serial.println(message);

  if (String(topic) != DELTA_TOPIC) return;

  DeserializationError err = deserializeJson(inputDoc, payload);
  if (err) {
    Serial.println("Error al parsear JSON recibido");
    return;
  }

  JsonObject state = inputDoc["state"].as<JsonObject>();
  if (state.containsKey("dispenser_state")) {
    String newState = state["dispenser_state"].as<String>();
    Serial.print("Nuevo estado recibido desde AWS: ");
    Serial.println(newState);
    dispenser->applyState(newState);
    reportShadow();
  }
}
