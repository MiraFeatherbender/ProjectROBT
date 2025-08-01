#ifndef CUSTOM_COMMAND_FACTORY_H
#define CUSTOM_COMMAND_FACTORY_H

#include <map>
#include <memory>
#include <Arduino.h>  // Assuming you use Arduino types like String

// Forward declarations of command classes
class DistanceCommand;
class DistanceQueryCommand;
class SleepCommand;
class WakeCommand;
class CalRangeCommand;
class CalRangeQuery;
class HardReset;
class CustomCommand;  // Don't forget the base class!

class CustomCommandFactory {
private:
  std::map<String, std::unique_ptr<CustomCommand>> commands;

public:
  CustomCommandFactory();                         // Constructor declaration
  CustomCommand* getCommand(const String& name);  // Method declaration
};

#endif  // CUSTOM_COMMAND_FACTORY_H
