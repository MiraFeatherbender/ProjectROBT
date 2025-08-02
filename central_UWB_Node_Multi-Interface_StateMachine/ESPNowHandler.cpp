#include "ESPNowHandler.h"

// Set up the default WiFi configuration.
const wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();

// Define static members.
ESPNowHandler* ESPNowHandler::_instance = nullptr;
MessageReceivedCallback ESPNowHandler::_externalReceiverCallback = nullptr;

ESPNowHandler::ESPNowHandler() {
  setInstance(this);
}

bool ESPNowHandler::init() {
  // Restart WiFi to clear any potential issues.
  esp_wifi_stop();
  esp_wifi_deinit();

  if (esp_wifi_init(&wifi_config) != ESP_OK) {
    Serial.println("Error initializing WiFi");
    return false;
  }

  WiFi.mode(WIFI_MODE_STA);
  if (esp_wifi_start() != ESP_OK) {
    Serial.println("Error starting WiFi");
    return false;
  }

  // Initialize ESP-NOW.
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return false;
  }

  // Register ESP-NOW callbacks.
  esp_now_register_recv_cb(ESPNowHandler::recvCallback);
  esp_now_register_send_cb(ESPNowHandler::sendCallback);

  return true;
}

bool ESPNowHandler::addPeer(const uint8_t* peerMAC) {
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerMAC, 6);
  peerInfo.channel = 0;  // Use the current channel.
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return false;
  }
  return true;
}

bool ESPNowHandler::sendMessage(const uint8_t* target, const uint8_t* data, size_t length, int delayMs) {
  esp_err_t result = esp_now_send(target, data, length);
  //Serial.printf("esp_now_send returned: %d\n", result);
  delay(delayMs);
  return (result == ESP_OK);
}

void ESPNowHandler::setMessageReceivedCallback(MessageReceivedCallback callback) {
  _externalReceiverCallback = callback;
}

void ESPNowHandler::onDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len) {
  // Default internal processing when no external callback is set.
  Serial.print("Default onDataRecv: Received data from: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", recv_info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
  // (Additional processing can be added here if desired.)
}

void ESPNowHandler::onDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  // Serial.print("ESP-NOW send callback: ");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SUCCESS" : "FAIL");
}

void ESPNowHandler::setInstance(ESPNowHandler* instance) {
  _instance = instance;
}

// The static receive callback delegates to the external callback if set,
// otherwise it calls the instance's internal onDataRecv.
void ESPNowHandler::recvCallback(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len) {
  if (_externalReceiverCallback != nullptr) {
    _externalReceiverCallback(recv_info, data, data_len);
  } else if (_instance) {
    _instance->onDataRecv(recv_info, data, data_len);
  }
}

// The static send callback delegates to the instance's onDataSent.
void ESPNowHandler::sendCallback(const uint8_t* mac_addr, esp_now_send_status_t status) {
  if (_instance) {
    _instance->onDataSent(mac_addr, status);
  }
}
