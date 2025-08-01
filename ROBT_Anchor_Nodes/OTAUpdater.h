#ifndef OTA_UPDATER_H
#define OTA_UPDATER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFi.h>

class OTAUpdater {
  public:
    OTAUpdater(const char* ssid, const char* password, const char* firmwareUrl);
    void updateFirmware();
  
  private:
    const char* _ssid;
    const char* _password;
    const char* _firmwareUrl;
};

#endif  // OTA_UPDATER_H
