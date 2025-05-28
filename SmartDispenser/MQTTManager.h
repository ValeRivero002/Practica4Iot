#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Dispenser.h"
#include "CommunicationManager.h"

class MQTTManager {
  public:
    MQTTManager(const char* broker, int port, const char* clientId);
    void begin(CommunicationManager& comm, Dispenser* dispenser);
    void loop();
    void reconnect();
    void reportShadow();
  private:
    PubSubClient client;
    StaticJsonDocument<256> inputDoc;
    StaticJsonDocument<256> outputDoc;
    char outputBuffer[256];
    Dispenser* dispenser;

    const char* broker;
    int port;
    const char* clientId;

    const char* UPDATE_TOPIC = "$aws/things/smart_dispenser_SN00001/shadow/update";
    const char* DELTA_TOPIC = "$aws/things/smart_dispenser_SN00001/shadow/update/delta";

    static void callbackStatic(char* topic, byte* payload, unsigned int length);
    void callbackInternal(char* topic, byte* payload, unsigned int length);
    static MQTTManager* instance;
};

#endif
