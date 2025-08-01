#include "EspNowHandler.h"

#include <string.h>
#include "Utils.h"
#include "ExternDefinitions.h"

SendCompleteCallback_t sendCompleteCallback = nullptr;
const wifi_init_config_t  wifi_config=WIFI_INIT_CONFIG_DEFAULT();

void initEspNow(const uint8_t *centralMAC) {
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_init(&wifi_config);
  WiFi.mode(WIFI_MODE_STA);
  esp_wifi_start();
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onDataSent);
  
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, centralMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add central node as peer");
    return;
  }
}

bool sendEspNowResponse(const char* response, int maxRetries, int delayMs) {
  if(strlen(response) < 3){
    Serial.println("Message is empty. Skipping transmission...");
    return true;
  }
  esp_err_t result = esp_now_send(NULL, (uint8_t *)response, strlen(response));
  Serial.printf("esp_now_send returned: %d for message: %s\n", result, response);
  delay(delayMs);
  return (result == ESP_OK);
}

void onDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len) {
  if (data_len < 2) {
    Serial.println("Received data too short.");
    return;
  }
  
  // Extract header information.
  uint8_t broadcastFlag = data[0];
  uint8_t cmdType = data[1];
  String payload = "";
  if (cmdType == CMD_STANDARD && data_len > 2) {
    char temp[250] = {0};
    int payloadLen = data_len - 2;
    memcpy(temp, &data[2], payloadLen);
    temp[payloadLen] = '\0';
    payload = String(temp);
  }

  if (broadcastFlag == 1) {
    applyRandomDelay(windowStart, windowEnd);
  }
  
  // Send ACK, factoring in random delay if broadcastFlag == 1.
  sendEspNowResponse("ACK", 0, 10);
  
    // Delegate received command to the state machine.
  stateMachine.setReceivedCommand(cmdType, payload);
}

// --- OnDataSent: ESP-NOW send callback ---
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("ESP-NOW send callback: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SUCCESS" : "FAIL");
  
  if (sendCompleteCallback != nullptr) {
    sendCompleteCallback(status);
    sendCompleteCallback = nullptr;
  }
}