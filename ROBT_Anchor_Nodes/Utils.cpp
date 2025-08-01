#include "Utils.h"

void readMacAddress(uint8_t* baseMac) {
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  if (ret == ESP_OK) {
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                  baseMac[0], baseMac[1], baseMac[2],
                  baseMac[3], baseMac[4], baseMac[5]);
  } else {
    Serial.println("Failed to read MAC address");
  }
}

void computeDelayWindow(const uint8_t* baseMac, uint16_t& windowStart, uint16_t& windowEnd) {
  uint32_t macHash = 0;
  for (int i = 0; i < 6; i++) {
    macHash = ((macHash << 5) + macHash) + baseMac[i];
  }
  const uint16_t TOTAL_DELAY_MS = 210;  // Adjust as needed.
  const uint8_t NUM_WINDOWS = 21;
  const uint16_t DELAY_PER_WINDOW_MS = TOTAL_DELAY_MS / NUM_WINDOWS;

  uint8_t delayWindowIndex = macHash % NUM_WINDOWS;
  windowStart = delayWindowIndex * DELAY_PER_WINDOW_MS;
  windowEnd = windowStart + DELAY_PER_WINDOW_MS;
}

void applyRandomDelay(uint16_t windowStart, uint16_t windowEnd) {
  uint16_t randomDelay = random(windowStart, windowEnd);
  delay(randomDelay);
}

void hardResetUWBSensor() {
  const int pinNRST = 9;
  pinMode(pinNRST, OUTPUT);
  digitalWrite(pinNRST, LOW);
  delay(100);
  digitalWrite(pinNRST, HIGH);
}

bool retryOperation(std::function<bool()> operation, int maxRetries, int delayMs) {
  for (int attempt = 0; attempt < maxRetries; attempt++) {
    if (operation()) {
      delay(delayMs);
      return true;  // Operation succeeded
    }
    Serial.printf("Retrying operation (%d/%d)...\n", attempt + 1, maxRetries);
  }
  Serial.println("Operation failed after retries.");
  return false;  // Operation failed after all retries
}

// Reads the sensor response from Serial1 and returns it.
String receiveSensorResponse() {
  String responseBuffer = "";
  unsigned long startTime = millis();
  const unsigned long timeout = 40;

  while (millis() - startTime < timeout) {
    if (Serial1.available()) {
      char receivedChar = char(Serial1.read());
      responseBuffer += receivedChar;
      startTime = millis();
      if (receivedChar == '\n' && responseBuffer.length() > 2) {
        responseBuffer.trim();
        if (responseBuffer.length() > 2) {
          responseBuffer += "\r\n";
          break;
        }
      }
    }
  }
  return responseBuffer;
}

// Attempt to execute custom command with parameters.
bool executeCommand(const String& commandName, const std::vector<String>& params, String* customReturn) {
  CustomCommand* command = commandFactory.getCommand(commandName);
  if (!command) {
    return false;  // Command not found
  }

  String result = command->execute(params);

  if (customReturn != nullptr) {
    *customReturn = result;
  }

  return true;
}
