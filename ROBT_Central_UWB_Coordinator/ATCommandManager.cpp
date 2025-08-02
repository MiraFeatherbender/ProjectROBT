#include "ATCommandStateManager.h"

ATCommandStateManager::ATCommandStateManager(const ATCommandMap &defaultMap)
  : defaultDefinitions(&defaultMap)  // Store pointer to the provided defaultMap
{
  // Initialize dynamic state with values from the static definitions.
  for (auto const &entry : *defaultDefinitions) {
    dynamicState[entry.first] = entry.second.defaultValue;
  }
}

bool ATCommandStateManager::parseResponse(const String &response, String &cmdToken, String &rawValue) const {
  if (!response.startsWith("+")) {
    return false;
  }
  int equalsIndex = response.indexOf('=');
  if (equalsIndex < 1) {
    return false;
  }
  cmdToken = response.substring(1, equalsIndex);
  rawValue = response.substring(equalsIndex + 1);
  rawValue.trim();
  return true;
}

ATResponseResult ATCommandStateManager::updateFromResponse(const String &response) {
  ATResponseResult result;
  result.updated = false;
  result.commandToken = "";
  result.convertedParameter = "";

  String cmdToken, rawValue;
  if (!parseResponse(response, cmdToken, rawValue)) {
    // Parsing failed; optionally log an error here.
    return result;
  }

  // Only update if this command exists in our dynamic state.
  auto it = dynamicState.find(cmdToken);
  if (it != dynamicState.end()) {
    // Optionally: update only if the value has actually changed.
    if (it->second != rawValue) {
      it->second = rawValue;
      result.updated = true;
    }
    result.commandToken = cmdToken;
    result.convertedParameter = lookupPlainValue(cmdToken, rawValue);
  }
  return result;
}


String ATCommandStateManager::lookupPlainValue(const String &commandToken, const String &rawValue) const {
  auto defIt = defaultDefinitions->find(commandToken);
  if (defIt != defaultDefinitions->end()) {
    auto &mapping = defIt->second.mapping;
    if (mapping.find(rawValue) != mapping.end()) {
      return mapping.at(rawValue);
    }
  }
  return rawValue;
}

String ATCommandStateManager::getPlainValue(const String &commandToken) const {
  auto it = dynamicState.find(commandToken);
  if (it != dynamicState.end()) {
    return lookupPlainValue(commandToken, it->second);
  }
  return "";
}

String ATCommandStateManager::getRawValue(const String &commandToken) const {
  auto it = dynamicState.find(commandToken);
  if (it != dynamicState.end()) {
    return it->second;
  }
  return "";
}

String ATCommandStateManager::buildSetCommand(const String &commandToken, const String &parameter) {
  return "AT+" + commandToken + "=" + parameter;
}

String ATCommandStateManager::buildQueryCommand(const String &commandToken) {
  return "AT+" + commandToken + "?";
}


const std::map<String, String> &ATCommandStateManager::getDynamicState() const {
  return dynamicState;
}

const ATCommandMap &ATCommandStateManager::getDefaultDefinitions() const {
  return *defaultDefinitions;
}