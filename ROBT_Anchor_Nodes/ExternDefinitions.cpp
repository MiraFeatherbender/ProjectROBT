#include "ExternDefinitions.h"

uint8_t baseMac[6];

uint16_t windowStart;
uint16_t windowEnd;

// OTA network credentials and firmware server URL
const char* otaSSID = "OTA-updates";
const char* otaPassword = "ESP32OTAupdates";
const char* firmwareUrl = "http://192.168.8.103:8080/Anchor_Nodes_DualCore_OTA.ino.bin";

//Create an OTAUpdater instance.
OTAUpdater otaUpdater(otaSSID, otaPassword, firmwareUrl);
StateMachine stateMachine(otaUpdater);
CustomCommandFactory commandFactory;