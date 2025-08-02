#ifndef ATCOMMANDDEFAULTS_H
#define ATCOMMANDDEFAULTS_H

#include <Arduino.h>
#include <map>

// -------------------------------------------------------------------------
// Basic AT command definition structure.
struct ATCommandDefinition {
  std::map<String, String> mapping;  // raw-to-plain mapping (if applicable)
  String defaultValue;               // default parameter value for this command
};

// Type alias for basic AT command map.
typedef std::map<String, ATCommandDefinition> ATCommandMap;

// Example UWB defaults:
static const ATCommandMap UWBDefaults = {
  { "MODE",           { { { "0", "TAG" }, { "1", "ANCHOR" }, { "2", "SLEEP" } }, "" } },
  { "NETWORKID",      { {}, "ROBT" } },
  { "IPR",            { { { "9600", "9600" }, { "57600", "57600" }, { "115200", "115200" } }, "115200" } },
  { "CHANNEL",        { { { "5", "6489.6MHZ" }, { "9", "7987.2MHZ" } }, "9" } },
  { "BANDWIDTH",      { { { "0", "850Kbps" }, { "1", "6.8Mbps" } }, "1" } },
  { "ADDRESS",        { {}, "" } },
  { "CPIN",           { {}, "D4F0734F8A19C4AD64B90FCAD249BFA0" } },
  { "TAGD",           { {}, "0,0" } },
  { "CAL",            { {}, "" } },
  { "UID",            { {}, "" } },
  { "MEAS_DISTANCE",  { {}, "OK" } },
  { "READ_DISTANCE",  { {}, "0" } },
  { "ERR",            { { { "1", "There is not \"enter\" or 0x0D 0x0A at the end of the AT Command." },
                          { "2", "The head of AT command is not \"AT\" string." },
                          { "3", "Parameter failure." },
                          { "4", "Command failure." },
                          { "5", "Unknown command." } }, "" } }
  // Add more set/query commands here, e.g.:
};

// -------------------------------------------------------------------------
// Extended structure for custom AT commands.
// This structure adds a second parameter field that can be used,
// for instance, to describe aspects of the return value.
// struct ATCustomCommandDefinition : public ATCommandDefinition {
//   String secondParameter;  // Additional parameter detail (e.g., label for return value)
// };

// Type alias for custom AT command map.
typedef std::map<String, ATCommandDefinition> ATCustomCommandMap;

// Format: { "COMMAND", { mapping, defaultValue, secondParameter } }
static const ATCustomCommandMap UWBCustom = {
    { "MEAS_DISTANCE", { { { "0", "RAW_READING" }, { "1", "MOVING_AVERAGE" }, { "2", "GAUSSIAN" } }, "1"} },
    { "READ_DISTANCE", { {}, ""} },
    { "CALRANGE", { {}, ""} },       // Set: calibrate against known distance (returns offset)
    { "SLEEP",    { {}, ""} },       // Action: put node to sleep (no query response)
    { "WAKE",     { {}, ""} }        // Action: wake node (no query response)
};


#endif  // ATCOMMANDDEFAULTS_H
