#include "UWBNode.h"
#include <set>

UWBNode::UWBNode(uint8_t nodeNum, const uint8_t* mac, String defMode, String defAddress)
  : OuterNode(nodeNum, mac, UWB, UWBDefaults), defaultMode(defMode), defaultAddress(defAddress) {
}

String UWBNode::getDefaultMode() const {
  return defaultMode;
}

std::map<String, String> UWBNode::getPerNodeDefaultSettings() const {
    return {
        {"MODE", defaultMode},
        {"ADDRESS", defaultAddress}
    };
}

std::set<String> UWBNode::getTokensToSkip() const {
    return {"MEAS_DISTANCE","READ_DISTANCE","ERR"};
}