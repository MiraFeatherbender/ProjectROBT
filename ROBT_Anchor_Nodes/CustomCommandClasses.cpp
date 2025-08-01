#include "CustomCommandFactory.h"
#include "CustomCommandClasses.h"
#include "EspNowHandler.h"
#include "Utils.h"
#include "ExternDefinitions.h"

String DistanceCommand::execute(const std::vector<String>& params) {
  // Get mode and numReadings, falling back to defaults if necessary
  String mode = params.size() > 0 ? params[0] : defaultValues[0];
  String numReadings = params.size() > 1 ? params[1] : defaultValues[1];

  Serial.println(mode + " " + numReadings);

  // Check if the mode exists in the mapping
  auto it = mapping.find(mode);
  if (it == mapping.end()) {
    Serial.println("Invalid mode for DISTANCE.");
    return "";  // Early exit if the mode is invalid
  }
  // Extract the enum and friendly name
  ProcessingMethod methodProcessor = it->second.first;
  String friendlyName = it->second.second;

  nReadings = numReadings.toInt();
  if (nReadings <= 0 || nReadings > maxReadings) {
    Serial.println("Invalid number of readings.");
    return "";
  }

  // Main logic for handling valid modes
  Serial.println("Handling DISTANCE command...");
  Serial.println("Mode: " + friendlyName);
  Serial.println("Number of Readings: " + numReadings);

  currentReadings = (mode.toInt() == 0) ? 0 : currentReadings;                       // Tracks the number of readings processed
  int requiredReadings = (mode.toInt() == 0) ? nReadings : std::max(21, nReadings);  // Determine required count dynamically

  //Collect readings
  do {
    // Shift all readings to the right, making space at readings[0]
    std::rotate(readings.rbegin(), readings.rbegin() + 1, readings.rend());

    requestReading(0);  // Collect the new reading and store it at readings[0]
    currentReadings++;  // Increment the counter
  } while (currentReadings < requiredReadings);

  String ok = (mode.toInt() == 0) ? "+OK\r\n" : "+MEAS_DISTANCE=OK\r\n";
  sendEspNowResponse(ok.c_str(), 1, 10);

  Serial.println("Calling the processor method for mode: " + friendlyName);
  // Call the appropriate processing method dynamically
  (this->*methodProcessor)();

  //Serial.println("Processed readings: " + result);
  return "";
}

void DistanceCommand::requestReading(int index) {
  String requestPhrase = "AT+ANCHOR_SEND=TAG,1,A\r\n";
  Serial1.print(requestPhrase);
  String receivePhrase;
  for (int i = 0; i < 2; i++) {
    receivePhrase = receiveSensorResponse();
    if (receivePhrase.startsWith("+ERR")) return;
    if (receivePhrase.startsWith("+OK")) { receivePhrase = receiveSensorResponse(); }
    if (receivePhrase.startsWith("+ANCHOR")) break;
  }
  readings[index] = parseReading(receivePhrase);
}

int DistanceCommand::parseReading(String receivePhrase) {

  int start = receivePhrase.lastIndexOf(',') + 1;             // Find the last comma and add 1 to skip it
  int end = receivePhrase.indexOf(" CM", start);              // Find " CM" starting from `start`
  String numberString = receivePhrase.substring(start, end);  // Extract the substring

  int result = numberString.toInt();  // Convert the substring to an integer

  return result;  // Add a random integer to the buffer
}

void DistanceCommand::processRawReading() {
  Serial.println("Processing RAW_READING...");
  String returnReadings = "";
  for (int i = 0; i < nReadings; ++i) {
    returnReadings.concat(String(readings[i]));  // Access directly from the class buffer
    if (i != nReadings - 1) {
      returnReadings.concat(",");  // Add comma only if not the last element
    }
  }
  //Serial.println(returnReadings);
}

void DistanceCommand::processMovingAverage() {
  // Ensure nReadings does not exceed the maximum buffer size
  if (nReadings > maxReadings) {
    nReadings = maxReadings;
  }

  // Define the window size and reference point
  int windowSize = std::max(21, nReadings);
  int centerReading = int(windowSize / 2);  // Zero-based indexing
  int halfWindow = int(nReadings / 2);

  // Determine the lower and upper index limits
  int lowerLimit = std::max(0, centerReading - halfWindow);
  int upperLimit = std::min(windowSize - 1, centerReading + halfWindow);

  // Use std::accumulate to sum the readings in the range
  int sum = std::accumulate(readings.begin() + lowerLimit, readings.begin() + upperLimit + 1, 0);

  // Calculate the moving average
  double response = double(sum) / nReadings;

  // Convert the result to a String and return it
  lastFilteredReading = String(response, 0);  // Optionally limit to 0 decimal places for clarity
}

void DistanceCommand::processGaussian() {
  Serial.println("Processing GAUSSIAN...");
  String returnReadings = "";
  for (int i = 0; i < 1; ++i) {
    returnReadings.concat(readings[i]);  // Access directly from the class buffer
    if (i != nReadings - 1) {
      returnReadings.concat(",");  // Add comma only if not the last element
    }
  }
  //return returnReadings;
}

String DistanceQueryCommand::execute(const std::vector<String>& params) {
  // Dynamically retrieve the DistanceCommand instance
  DistanceCommand* distanceCommand = static_cast<DistanceCommand*>(
    commandFactory.getCommand("AT+MEAS_DISTANCE"));
  if (!distanceCommand) {
    Serial.println("DistanceCommand instance not found.");
    return "+ERR: DistanceCommand not available\r\n";
  }

  // Retrieve the last filtered reading
  String result = distanceCommand->getLastFilteredReading();
  if (result.isEmpty()) {
    Serial.println("No reading available for query.");
    return "+ERR: No reading available\r\n";
  }

  // Return the result for transmission to the central node
  result.trim();
  return "+READ_DISTANCE=" + result + "\r\n";  // Add proper AT response formatting
}

String SleepCommand::execute(const std::vector<String>& params) {
  Serial.println("Executing SLEEP command...");
  sendCommandMultipleTimes("AT+MODE=2", 1);  // Hardcoded behavior
  return "UWB Sensor is asleep.";
}

String WakeCommand::execute(const std::vector<String>& params) {
  Serial.println("Executing WAKE command...");
  sendCommandMultipleTimes("AT", 2);
  return "UWB Sensor is awake.";
}

String CalRangeCommand::execute(const std::vector<String>& params) {
  // Dynamically retrieve the DistanceCommand instance
  DistanceCommand* distanceCommand = static_cast<DistanceCommand*>(
    commandFactory.getCommand("AT+MEAS_DISTANCE"));
  if (!distanceCommand) {
    Serial.println("DistanceCommand instance not found.");
    return "+ERR: DistanceCommand not available\r\n";
  }

  // Execute the distance command with required parameters
  Serial.println("Executing AT+MEAS_DISTANCE=0,50...");
  distanceCommand->execute({ "0", "50" });

  // Retrieve the readings after execution
  const auto& readings = distanceCommand->getReadings();
  if (readings.empty()) {
    Serial.println("No readings available for calibration.");
    return "+ERR: No readings available\r\n";
  }

  // Transfer readings to a vector
  std::vector<int> readingsVector(readings.begin(), readings.end());

  calibrate(readingsVector);

  return "+CAL_RANGE=OK\r\n";
}
void CalRangeCommand::calibrate(std::vector<int>& readings) {

  std::sort(readings.begin(), readings.end());

  double mean = std::accumulate(readings.begin(), readings.end(), 0.0) / readings.size();
  double variance = std::accumulate(readings.begin(), readings.end(), 0.0,
                                    [mean](double acc, int value) {
                                      return acc + std::pow(value - mean, 2);
                                    })
                    / readings.size();

  double stddev = std::sqrt(variance);

  readings.erase(std::remove_if(readings.begin(), readings.end(),
                                [mean, stddev](int value) {
                                  double zScore = (value - mean) / stddev;
                                  return std::abs(zScore) > 2.0;  // Threshold for outliers
                                }),
                 readings.end());

  average = static_cast<int>(std::accumulate(readings.begin(), readings.end(), 0.0) / readings.size());

  Serial.printf("Average of Filtered Readings: %d\n", average);
}

String CalRangeQuery::execute(const std::vector<String>& params){
  // Dynamically retrieve the CalRangeCommand instance
  CalRangeCommand* calRangeCommand = static_cast<CalRangeCommand*>(
    commandFactory.getCommand("AT+CAL_RANGE"));
  if (!calRangeCommand) {
    Serial.println("CalRangeCommand instance not found.");
    return "+ERR: CalRangeCommand not available\r\n";
  }

  // Retrieve the last calibrated reading
  String result = String(calRangeCommand->getLastCalReading());
  if (result.isEmpty()) {
    Serial.println("No reading available for query.");
    return "+ERR: No reading available\r\n";
  }

  // Return the result for transmission to the central node
  result.trim();
  return "+READ_RANGE=" + result + "\r\n";  // Add proper AT response formatting
}



void sendCommandMultipleTimes(const String& cmd, int cycles) {
  for (int i = 0; i < cycles; i++) {
    String formattedCmd = cmd + "\r\n";
    Serial.print(formattedCmd);
    Serial1.print(formattedCmd);

    int timeoutThreshold = millis() + 50;
    waitForResponse(timeoutThreshold);  // Call the helper function
  }
}

void waitForResponse(int timeout) {
  while (millis() < timeout) {
    if (Serial1.available() > 0) {
      String response = Serial1.readStringUntil('\n');
      response.trim();
      response.concat("\r\n");
      sendEspNowResponse(response.c_str(), 1, 10);
      Serial.print(response);
      return;
    }
  }
}

String HardReset::execute(const std::vector<String>& params) {
  hardResetUWBSensor();
  return "UWB Hard Reset";
}