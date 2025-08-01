#ifndef ESP_NOW_HANDLER_H
#define ESP_NOW_HANDLER_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Define the send-complete callback type.
typedef void (*SendCompleteCallback_t)(esp_now_send_status_t status);

// Declare global send callback variable.
extern SendCompleteCallback_t sendCompleteCallback;

// Function prototypes.
void initEspNow(const uint8_t *centralMAC);
bool sendEspNowResponse(const char* response, int maxRetries = 3, int delayMs = 10);
void onDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int data_len);
void onDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status);

#endif  // ESP_NOW_HANDLER_H
