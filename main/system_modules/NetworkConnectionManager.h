#ifndef NETWORK_CONNECTION_MANAGER_H
#define NETWORK_CONNECTION_MANAGER_H

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include "NetworkCredentialManager.h"
#include "NetworkStateManager.h"
#include "../Config.h"

class NetworkConnectionManager {
public:
    NetworkConnectionManager(NetworkCredentialManager& credMgr, NetworkStateManager& stateMgr)
        : credentialManager(credMgr), stateManager(stateMgr), lastAttemptTime(0) {}

    void connectToHub() {
        if (stateManager.getCurrentNetworkState() != HUB_NETWORK) {
            stateManager.updateNetworkState(CONNECTING);
            WiFi.begin(HUB_WIFI_SSID, HUB_WIFI_PASSWORD);
        }
    }

    void connectToCustom() {
        if (credentialManager.hasCustomCredentials()) {
            auto creds = credentialManager.getCustomCredentials();
            stateManager.updateNetworkState(CONNECTING);
            WiFi.begin(creds.first.c_str(), creds.second.c_str());
        } else {
            startCaptivePortal();
        }
    }

    void startCaptivePortal() {
        if (stateManager.getCurrentNetworkState() != CAPTIVE_PORTAL) {
            stateManager.updateNetworkState(CAPTIVE_PORTAL);
            WiFiManager wifiManager;
            wifiManager.setTimeout(180);
            wifiManager.setSaveConfigCallback([this]() {
                auto ssid = WiFi.SSID();
                auto pass = WiFi.psk();
                credentialManager.saveCustomCredentials(ssid.c_str(), pass.c_str());
                connectToCustom();  // Attempt to connect with new credentials
            });
            wifiManager.startConfigPortal("ConfigPortal");
        }
    }

    void handleNetworkSwitching() {
        if (WiFi.status() == WL_CONNECTED) {
            if (stateManager.getCurrentNetworkState() == CONNECTING) {
                String ssid = WiFi.SSID();
                if (ssid == HUB_WIFI_SSID) {
                    stateManager.updateNetworkState(HUB_NETWORK);
                } else {
                    stateManager.updateNetworkState(CUSTOM_NETWORK);
                }
            }
        } else if (millis() - lastAttemptTime > 30000) {
            lastAttemptTime = millis();
            switch (stateManager.getCurrentNetworkState()) {
                case HUB_NETWORK:
                    connectToHub();
                    break;
                case CUSTOM_NETWORK:
                    connectToCustom();
                    break;
                default:
                    break;  // No action needed if in CAPTIVE_PORTAL or other states
            }
        }
    }

private:
    NetworkCredentialManager& credentialManager;
    NetworkStateManager& stateManager;
    unsigned long lastAttemptTime;
};

#endif // NETWORK_CONNECTION_MANAGER_H
