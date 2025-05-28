#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <WiFi.h>
#include <WiFiClientSecure.h>

class CommunicationManager {
  public:
    CommunicationManager(const char* ssid, const char* pass,
                         const char* rootCA, const char* cert, const char* privateKey);
    void connectWiFi();
    WiFiClientSecure& getSecureClient();

  private:
    const char* ssid;
    const char* pass;
    const char* rootCA;
    const char* cert;
    const char* privateKey;
    WiFiClientSecure secureClient;
};

#endif
