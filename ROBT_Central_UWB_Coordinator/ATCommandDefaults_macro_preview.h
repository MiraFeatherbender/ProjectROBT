#ifndef ATCOMMANDDEFAULTS_MACRO_PREVIEW_H
#define ATCOMMANDDEFAULTS_MACRO_PREVIEW_H

#include <Arduino.h>
#include <map>

// Macro to help create parameter mapping
#define ATCMD_MAP(...) std::map<String, String> { __VA_ARGS__ }
// Macro to help create a command entry
#define ATCMD_ENTRY(name, map, def) { name, { map, def } }

// -------------------------------------------------------------------------
// Basic AT command definition structure.
struct ATCommandDefinition {
  std::map<String, String> mapping;  // raw-to-plain mapping (if applicable)
  String defaultValue;               // default parameter value for this command
};

typedef std::map<String, ATCommandDefinition> ATCommandMap;

// Example UWB defaults using macros:
static const ATCommandMap UWBDefaults = {
  ATCMD_ENTRY("MODE",       ATCMD_MAP({ "0", "TAG" }, { "1", "ANCHOR" }, { "2", "SLEEP" }), ""),
  ATCMD_ENTRY("NETWORKID",  ATCMD_MAP(), "ROBT"),
  ATCMD_ENTRY("IPR",        ATCMD_MAP({ "9600", "9600" }, { "57600", "57600" }, { "115200", "115200" }), "115200"),
  ATCMD_ENTRY("CHANNEL",    ATCMD_MAP({ "5", "6489.6MHZ" }, { "9", "7987.2MHZ" }), "9"),
  ATCMD_ENTRY("BANDWIDTH",  ATCMD_MAP({ "0", "850Kbps" }, { "1", "6.8Mbps" }), "1"),
  ATCMD_ENTRY("ADDRESS",    ATCMD_MAP(), ""),
  ATCMD_ENTRY("CPIN",       ATCMD_MAP(), "D4F0734F8A19C4AD64B90FCAD249BFA0"),
  ATCMD_ENTRY("TAGD",       ATCMD_MAP(), "0,0"),
  ATCMD_ENTRY("CAL",        ATCMD_MAP(), ""),
  ATCMD_ENTRY("UID",        ATCMD_MAP(), ""),
  ATCMD_ENTRY("MEAS_DISTANCE", ATCMD_MAP(), "OK"),
  ATCMD_ENTRY("READ_DISTANCE", ATCMD_MAP(), "0"),
  ATCMD_ENTRY("ERR", ATCMD_MAP(
    { "1", "There is not \"enter\" or 0x0D 0x0A at the end of the AT Command." },
    { "2", "The head of AT command is not \"AT\" string." },
    { "3", "Parameter failure." },
    { "4", "Command failure." },
    { "5", "Unknown command." }
  ), "")
  // Add more set/query commands here, e.g.:
};

#endif // ATCOMMANDDEFAULTS_MACRO_PREVIEW_H
