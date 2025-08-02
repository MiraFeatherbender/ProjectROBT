#ifndef UWBNODE_H
#define UWBNODE_H

#include "OuterNode.h"

class UWBNode : public OuterNode {
private:
  String defaultMode;
  String defaultAddress;


public:
  UWBNode(uint8_t nodeNum, const uint8_t* mac, String mode, String address);

  // Optional accessor methods.
  String getDefaultMode() const;

  virtual std::map<String, String> getPerNodeDefaultSettings() const;
  virtual std::set<String> getTokensToSkip() const;
  bool isAnchor() const override {
    return defaultMode == "1";  // "1" represents Anchor mode
  }
};

#endif  // UWBNODE_H
