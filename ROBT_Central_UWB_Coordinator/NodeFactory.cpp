#include "NodeFactory.h"
#include "UWBNode.h"
#include <array>

struct NodeConfig {
  uint8_t nodeNumber;
  uint8_t macAddress[6];
  NodeType type;
  String param1;
  String param2;
};

// Place your static configuration here:
static const std::array<NodeConfig, 7> nodeConfigs{
  { { 1, { 0xE4, 0xB3, 0x23, 0xC2, 0xAF, 0xB4 }, UWB, "1", "1" },
    { 2, { 0xE4, 0xB3, 0x23, 0xC1, 0x57, 0xEC }, UWB, "1", "2" },
    { 3, { 0x34, 0xCD, 0xB0, 0xD2, 0xDC, 0xA4 }, UWB, "1", "3" },
    { 4, { 0xE4, 0xB3, 0x23, 0xC0, 0x2B, 0x04 }, UWB, "1", "4" },
    { 5, { 0x34, 0xCD, 0xB0, 0xD1, 0xF3, 0xCC }, UWB, "1", "5" },
    { 6, { 0x64, 0xe8, 0x33, 0xac, 0x7e, 0x70 }, UWB, "0", "TAG" } }
    // { 7, { 0xe4, 0xb3, 0x23, 0xc2, 0xc9, 0x6c }, UWB, "1", "7" } } //spare outer node for additional testing
};

std::vector<std::unique_ptr<OuterNode>> NodeFactory::createNodes() {
  std::vector<std::unique_ptr<OuterNode>> nodes;

  for (const auto &config : nodeConfigs) {
    // A switch or if‐else determines which type to create.
    switch (config.type) {
      case UWB:
        nodes.push_back(std::make_unique<UWBNode>(config.nodeNumber, config.macAddress,
                                                  config.param1, config.param2));
        break;
      // Add other cases for different node types if needed.
      default:
        Serial.print("Unknown node type for node ");
        Serial.println(config.nodeNumber);
        continue;  // Skip to next configuration.
    }
  }

  return nodes;
}
