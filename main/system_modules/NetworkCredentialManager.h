#ifndef NETWORK_CREDENTIAL_MANAGER_H
#define NETWORK_CREDENTIAL_MANAGER_H

#include <LittleFS.h>
#include <string>

class NetworkCredentialManager {
public:
    NetworkCredentialManager() {
        if (!LittleFS.begin()) {
            Serial.println("An Error has occurred while mounting LittleFS");
        }
    }

    bool hasCustomCredentials() const {
        return LittleFS.exists("/credentials.txt");
    }

    std::pair<std::string, std::string> getCustomCredentials() const {
        File file = LittleFS.open("/credentials.txt", "r");
        if (!file) {
            return {"", ""};
        }
        std::string ssid = file.readStringUntil('\n').c_str();
        std::string pass = file.readStringUntil('\n').c_str();
        file.close();
        return {ssid, pass};
    }

    void saveCustomCredentials(const char* ssid, const char* pass) {
        File file = LittleFS.open("/credentials.txt", "w");
        if (file) {
            file.println(ssid);
            file.println(pass);
            file.close();
        }
    }

    void clearCustomCredentials() {
        LittleFS.remove("/credentials.txt");
    }
};

#endif // NETWORK_CREDENTIAL_MANAGER_H
