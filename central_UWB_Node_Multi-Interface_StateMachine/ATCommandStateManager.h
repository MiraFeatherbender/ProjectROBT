#ifndef ATCOMMANDSTATEMANAGER_H
#define ATCOMMANDSTATEMANAGER_H

#include <Arduino.h>
#include <map>
#include "ATCommandDefaults.h"  // Contains UWBDefaults, etc.

struct ATCommandDataDynamic {
  String currentValue;
};

struct ATResponseResult {
  bool updated;               // true if the response was parsed and updated an entry
  String commandToken;        // e.g. "MODE"
  String convertedParameter;  // e.g. "ANCHOR"
};

class ATCommandStateManager {
public:

  // Constructor: initializes dynamic state from the passed static defaults.
  ATCommandStateManager(const ATCommandMap &defaultMap);

  bool parseResponse(const String &response, String &cmdToken, String &rawValue) const;

  // Updates the dynamic state using a response string.
  // Expected format: "+<command>=<value>"
  // Returns true if a command was recognized and updated.
  ATResponseResult updateFromResponse(const String &response);

  // Retrieves the plain-English conversion for a command using the static defaults.
  // Looks up command in the static defaults from ATCommandDefaults.h,
  // using the dynamic current value.
  String getPlainValue(const String &commandToken) const;

  // Retrieves the raw current value for a command.
  String getRawValue(const String &commandToken) const;

  // Optionally, a function to build a query command (or you could use the global helper).
  static String buildSetCommand(const String &commandToken, const String &parameter);
  static String buildQueryCommand(const String &commandToken);

  const std::map<String, String> &getDynamicState() const;

  const ATCommandMap &getDefaultDefinitions() const;
private:
  // Dynamic state mapping: command token -> current value.
  std::map<String, String> dynamicState;

  // A reference (or copy) of the static defaults for reference.
  const ATCommandMap *defaultDefinitions;

  // Helper function to look up the plain value from the static mapping.
  String lookupPlainValue(const String &commandToken, const String &rawValue) const;
};

#endif  // ATCOMMANDSTATEMANAGER_H
