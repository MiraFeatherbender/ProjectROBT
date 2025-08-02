#ifndef OUTERNODE_H
#define OUTERNODE_H

#include <Arduino.h>
#include <string.h>
#include "ATCommandStateManager.h"
#include <set>
#include "Mode.h"

enum NodeType { UWB,
                DIRECTION_FINDER,
                MOTOR_DRIVER };

#define CMD_STANDARD 0x00
#define CMD_OTA 0x01

class OuterNode {
protected:
  uint8_t nodeNumber;
  uint8_t macAddress[6];
  NodeType type;
  bool waitingForAck;
  bool waitingForResponse;
  bool active;
  unsigned long startTime;
  ATCommandStateManager atStateManager;
  virtual String determineExpectedValue(const String &token, const String &currentValue) const;
  std::function<void(const ATResponseResult &)> onResponseCallback;  // Generic callback


public:
  OuterNode(uint8_t nodeNum, const uint8_t *mac, NodeType nodeType, const ATCommandMap &defaultMap);
  virtual ~OuterNode();
  virtual void initialize();
  virtual void synchronizeSettings();

  bool isActive() const;
  bool isWaitingForAck() const;
  bool isWaitingForResponse() const;
  unsigned long getStartTime() const;
  uint8_t getNodeNumber() const;
  const uint8_t *getMAC() const;
  NodeType getType() const;
  virtual String getExpectedCommand() const {
    return "";
  }

  virtual std::map<String, String> getPerNodeDefaultSettings() const = 0;

  void setWaitingForAck(bool status);
  void setWaitingForResponse(bool status);
  void setStartTime(unsigned long t);

  virtual void sendQuery(const String &cmd);
  virtual bool sendCommand(const String &cmd);
  virtual void handleResponse(const String &response);
  virtual std::set<String> getTokensToSkip() const = 0;
  virtual bool isAnchor() const {
    return false;
  }
  void setResponseCallback(std::function<void(const ATResponseResult &)> callback) {
    onResponseCallback = callback;
  }
};

#endif  // OUTERNODE_H
