#ifndef MODE_H
#define MODE_H
#include <map>

enum class Mode {  // Scoped enum for safety
  FREERUN,
  SINGLERUN,
  MANUAL,
  INACTIVE
};

static const std::map<String, Mode> modeMap = {  // Encapsulated modeMap
  { "FREERUN", Mode::FREERUN },
  { "SINGLERUN", Mode::SINGLERUN},
  { "MANUAL", Mode::MANUAL },
  { "INACTIVE", Mode::INACTIVE }
};

static String modeToString(Mode mode) {
  for (const auto& pair : modeMap) {
    if (pair.second == mode) {
      return pair.first;
    }
  }
  return "UNKNOWN";
}


#endif  // MODE_H
