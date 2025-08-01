#include "EspNowHandler.h"
#include "OTAUpdater.h"
#include "ExternDefinitions.h"
#include "Utils.h"

OTAUpdater::OTAUpdater(const char* ssid, const char* password, const char* firmwareUrl)
  : _ssid(ssid), _password(password), _firmwareUrl(firmwareUrl) { }

void OTAUpdater::updateFirmware() {
  Serial.println("Putting UWB Sensor to sleep...");
  executeCommand("AT+WAKE");
  delay(50);
  executeCommand("AT+SLEEP");

  Serial.println("Performing OTA update...");
  WiFi.begin(_ssid, _password);
  
  const int wifiTimeout = 30000;    // 30 sec timeout
  unsigned long startTime = millis();
  while(WiFi.status() != WL_CONNECTED && (millis() - startTime) < wifiTimeout) {
    Serial.print(".");
    delay(500);
  }
  
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to OTA Wi-Fi network.");
    WiFi.disconnect(true);
    return;
  }
  
  Serial.println();
  Serial.print("Connected to OTA Wi-Fi. Local IP: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;
  http.begin(_firmwareUrl);
  int httpCode = http.GET();
  
  if(httpCode == HTTP_CODE_OK) {
    int contentLength = http.getSize();
    Serial.printf("Firmware size: %d bytes\n", contentLength);
    if(contentLength > 0 && Update.begin(contentLength)) {
      Serial.println("Downloading firmware...");
      WiFiClient *client = http.getStreamPtr();
      size_t written = 0;
      uint8_t buff[128];
      
      unsigned long lastDataTime = millis();
      while(written < contentLength && (millis() - lastDataTime) < 10000) { // 10 sec data stall timeout
        if (client->available()) {
          int len = client->readBytes(buff, sizeof(buff));
          written += Update.write(buff, len);
          lastDataTime = millis();
          Serial.printf("Written: %d/%d bytes\r", written, contentLength);
          Serial.println();
        } else {
          delay(10);
        }
      }
      Serial.println(); // newline after progress
      
      if(written == contentLength) {
        Serial.printf("Successfully written %d bytes.\n", written);
      } else {
        Serial.printf("Incomplete firmware written: %d/%d bytes.\n", written, contentLength);
      }
      
      if(Update.end()) {
        http.end();
        WiFi.disconnect(true);
        initEspNow(centralNodeMAC);
        if(Update.isFinished()) {
          String successMsg = "OTA update complete. Rebooting...\r\n";
          sendEspNowResponse(successMsg.c_str(), 0, 1000);
          Serial.print(successMsg);
          ESP.restart();
        } else {
          String errorMsg = "OTA update not finished. Something went wrong.\r\n";
          sendEspNowResponse(errorMsg.c_str(), 0, 10);
          Serial.print(errorMsg);
        }
      } else {
        String errorMsg = "Update failed. Error: " + String(Update.getError()) + "\r\n";
        sendEspNowResponse(errorMsg.c_str(), 0, 10);
        Serial.print(errorMsg);
      }
    } else {
      String errorMsg = "Not enough space or invalid content length.";
      sendEspNowResponse(errorMsg.c_str(), 0, 10);
      Serial.print(errorMsg);
    }
  } else {
    String errorMsg = "HTTP GET failed, error: " + http.errorToString(httpCode) + "\r\n";
    sendEspNowResponse(errorMsg.c_str(), 0, 10);
    Serial.print(errorMsg);
  }
  
  http.end();
  WiFi.disconnect(true);
  Serial.println("Wi-Fi disconnected after OTA update.");
}
