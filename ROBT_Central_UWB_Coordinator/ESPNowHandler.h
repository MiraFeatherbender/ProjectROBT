#ifndef ESPNOWHANDLER_H
#define ESPNOWHANDLER_H

#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

// Define a callback type for received messages.
typedef void (*MessageReceivedCallback)(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len);

class ESPNowHandler {
public:
  // Constructor.
  ESPNowHandler();

  // Initializes WiFi and ESP-NOW.
  bool init();

  // Registers a peer (an outer node) with its MAC address.
  bool addPeer(const uint8_t* peerMAC);

  // Sends a message via ESP-NOW; if target is NULL then a broadcast is performed.
  bool sendMessage(const uint8_t* target, const uint8_t* data, size_t length, int delayMs = 10);

  // Set the external callback that will handle message processing (ACK, responses, etc.)
  void setMessageReceivedCallback(MessageReceivedCallback callback);

  // This instance method can be used as a default receiver (if no external callback is set).
  void onDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len);

  void onDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);

  // Set our singleton instance pointer for static callbacks.
  static void setInstance(ESPNowHandler* instance);

private:
  // Singleton instance pointer.
  static ESPNowHandler* _instance;

  // The external message received callback provided by the main app.
  static MessageReceivedCallback _externalReceiverCallback;

  // Static callback for receiving data.
  static void recvCallback(const esp_now_recv_info_t* recv_info, const uint8_t* data, int data_len);

  // Static callback for handling send status.
  static void sendCallback(const uint8_t* mac_addr, esp_now_send_status_t status);
};

#endif  // ESPNOWHANDLER_H
