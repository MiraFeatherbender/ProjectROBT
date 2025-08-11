#line 1 "C:\\Users\\jonat\\OneDrive\\Old Documents\\GitHub\\ProjectROBT\\ROBT_Leg_Controller\\NVSManager.h"
#ifndef NVS_MANAGER_H
#define NVS_MANAGER_H

#include "FlashStorageTypes.h"
#include <Preferences.h>

class NVSManager {
public:
    // Generic template for storing any summary type to NVS
    template<typename SummaryType>
    static bool storeSummary(const SummaryType& summary) {
        Preferences prefs;
        if (!prefs.begin(SummaryType::nvs_namespace, false)) {
            return false;
        }
        auto kv = serializeSummary(summary);
        for (const auto& pair : kv) {
            const std::string& key = pair.first;
            if (std::holds_alternative<int32_t>(pair.second)) {
                prefs.putInt(key.c_str(), std::get<int32_t>(pair.second));
            } else if (std::holds_alternative<float>(pair.second)) {
                prefs.putFloat(key.c_str(), std::get<float>(pair.second));
            } else if (std::holds_alternative<std::string>(pair.second)) {
                prefs.putString(key.c_str(), std::get<std::string>(pair.second).c_str());
            }
        }
        prefs.end();
        return true;
    }

    // Generic template for printing any summary type
    template<typename SummaryType>
    static bool printSummaryToSerial(const SummaryType& summary) {
        Serial.print("[NVSManager] Namespace: ");
        Serial.println(SummaryType::nvs_namespace);
        Serial.println("[NVSManager] Summary contents:");
        auto kv = serializeSummary(summary); // Calls correct overload
        for (const auto& pair : kv) {
            Serial.print(pair.first.c_str());
            Serial.print(": ");
            if (std::holds_alternative<int32_t>(pair.second)) {
                Serial.println(std::get<int32_t>(pair.second));
            } else if (std::holds_alternative<float>(pair.second)) {
                Serial.println(std::get<float>(pair.second), 4);
            } else if (std::holds_alternative<std::string>(pair.second)) {
                Serial.println(std::get<std::string>(pair.second).c_str());
            }
        }
        return true;
    }

    // Generic template for reading and deserializing any summary type
    template<typename SummaryType>
    static bool readAndDeserializeSummary(SummaryType& summary) {
        Preferences prefs;
        if (!prefs.begin(SummaryType::nvs_namespace, true)) {
            return false;
        }
        auto expectedMap = serializeSummary(SummaryType{});
        std::map<std::string, NVSValue> kv;
        bool allFound = true;
        for (const auto& pair : expectedMap) {
            const std::string& key = pair.first;
            if (std::holds_alternative<int32_t>(pair.second)) {
                if (!prefs.isKey(key.c_str())) { allFound = false; break; }
                kv[key] = prefs.getInt(key.c_str(), 0);
            } else if (std::holds_alternative<float>(pair.second)) {
                if (!prefs.isKey(key.c_str())) { allFound = false; break; }
                kv[key] = prefs.getFloat(key.c_str(), 0.0f);
            } else if (std::holds_alternative<std::string>(pair.second)) {
                if (!prefs.isKey(key.c_str())) { allFound = false; break; }
                kv[key] = std::string(prefs.getString(key.c_str(), "").c_str());
            }
        }
        prefs.end();
        if (allFound) {
            deserializeSummary(kv, summary);
            return true;
        }
        return false;
    }
};

#endif // NVS_MANAGER_H