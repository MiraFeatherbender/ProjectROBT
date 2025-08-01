
#include "CustomCommandFactory.h"
#include "CustomCommandClasses.h"  
#include "ExternDefinitions.h"

CustomCommandFactory::CustomCommandFactory() {
  // Register commands here
  commands["AT+MEAS_DISTANCE"] = std::make_unique<DistanceCommand>();
  commands["AT+READ_DISTANCE"] = std::make_unique<DistanceQueryCommand>();
  commands["AT+SLEEP"] = std::make_unique<SleepCommand>();
  commands["AT+WAKE"] = std::make_unique<WakeCommand>();
  commands["AT+CAL_RANGE"] = std::make_unique<CalRangeCommand>();
  commands["AT+READ_RANGE"] = std::make_unique<CalRangeQuery>();
  commands["AT+HARDRESET"] = std::make_unique<HardReset>();
}

CustomCommand* CustomCommandFactory::getCommand(const String& name) {
  auto it = commands.find(name);
  return (it != commands.end()) ? it->second.get() : nullptr;
}