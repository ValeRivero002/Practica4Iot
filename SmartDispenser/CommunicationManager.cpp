#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(const char* ssid, const char* pass,
                                           const char* rootCA, const char* cert, const char* privateKey)
  : ssid(ssid), pass(pass), rootCA(rootCA), cert(cert), privateKey(privateKey) {}

void CommunicationManager::connectWiFi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nWiFi OK, IP: " + WiFi.localIP().toString());

  secureClient.setCACert(rootCA);
  secureClient.setCertificate(cert);
  secureClient.setPrivateKey(privateKey);
}

WiFiClientSecure& CommunicationManager::getSecureClient() {
  return secureClient;
}
