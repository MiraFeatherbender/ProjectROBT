#ifndef CUSTOM_COMMAND_CLASSES_H
#define CUSTOM_COMMAND_CLASSES_H

#include <Arduino.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <string>
#include <numeric>

void sendCommandMultipleTimes(const String& cmd, int cycles);
void waitForResponse(int timeout);

// Define the base class
class CustomCommand {
public:
  virtual ~CustomCommand() {}
  virtual String execute(const std::vector<String>& params) = 0;  // Command-specific logic
  virtual std::vector<String> getDefaultValues() const {
    return {};
  }  // Get default parameters
};

// Define derived commands
class DistanceCommand : public CustomCommand {
private:
  static const int maxReadings = 50;      // Fixed buffer size
  std::array<int, maxReadings> readings;  // Shared buffer for all methods
  int nReadings = 0;                      // Number of valid readings in the buffer
  int currentReadings = 0;
  String UWBTag = "TAG";
  String lastFilteredReading = "";

  using ProcessingMethod = void (DistanceCommand::*)();  // No need to pass nReadings

  // Map: mode code -> {processing method, friendly name}
  std::map<String, std::pair<ProcessingMethod, String>> mapping = {
    { "0", { &DistanceCommand::processRawReading, "RAW_READING" } },
    { "1", { &DistanceCommand::processMovingAverage, "MOVING_AVERAGE" } },
    { "2", { &DistanceCommand::processGaussian, "GAUSSIAN" } }
  };

  std::vector<String> defaultValues = { "1", "5" };  // Default mode and readings

public:
  String execute(const std::vector<String>& params) override;

  void requestReading(int index);
  int parseReading(String receivePhrase);

  // Internal processing methods for each mode
  void processRawReading();
  void processMovingAverage();
  void processGaussian();

  String getLastFilteredReading() const {
    return lastFilteredReading;
  }
  const std::array<int, maxReadings>& getReadings() const {
    return readings;
  }
  std::vector<String> getDefaultValues() const override {
    return defaultValues;
  }
};

class DistanceQueryCommand : public CustomCommand {
public:
  String execute(const std::vector<String>& params) override;
};

class SleepCommand : public CustomCommand {
public:
  String execute(const std::vector<String>& params) override;
};

class WakeCommand : public CustomCommand {
public:
  String execute(const std::vector<String>& params) override;
};

class CalRangeCommand : public CustomCommand {
private:
  int average;
public:
  String execute(const std::vector<String>& params) override;
  void calibrate(std::vector<int>& readings);
  int getLastCalReading() {
    return average;
  }
};

class CalRangeQuery : public CustomCommand {
public:
  String execute(const std::vector<String>& params) override;
};

class HardReset : public CustomCommand {
public:
  String execute(const std::vector<String>& params) override;
};

#endif  // CUSTOM_COMMAND_Classes_H
