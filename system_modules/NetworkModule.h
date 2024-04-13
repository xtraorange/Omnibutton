#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include "../BaseModule.h"
#include "NetworkConnectionManager.h"
#include "NetworkCredentialManager.h"
#include "NetworkStateManager.h"

class NetworkModule : public BaseModule {
public:
    NetworkModule(EventManager& evtManager, StateManager& stateMgr)
        : BaseModule(evtManager, stateMgr), 
          credentialManager(),
          networkStateManager(stateMgr, evtManager),
          connectionManager(credentialManager, networkStateManager) {
        evtManager.registerListener("NETWORK_SWITCH_TO_HUB", [this](std::string) { connectionManager.connectToHub(); });
        evtManager.registerListener("NETWORK_SWITCH_TO_CUSTOM", [this](std::string) { connectionManager.connectToCustom(); });
        evtManager.registerListener("NETWORK_CLEAR_CUSTOM_CREDENTIALS", [this](std::string) { credentialManager.clearCustomCredentials(); });
    }

    void initialize() override {
        WiFi.mode(WIFI_STA);
        NetworkState lastState = networkStateManager.loadNetworkState();
        if (lastState == CUSTOM_NETWORK && credentialManager.hasCustomCredentials()) {
            connectionManager.connectToCustom();
        } else {
            connectionManager.connectToHub();
        }
    }

    void update() override {
        connectionManager.handleNetworkSwitching();
    }

private:
    NetworkCredentialManager credentialManager;
    NetworkStateManager networkStateManager;
    NetworkConnectionManager connectionManager;
};

#endif // NETWORK_MODULE_H
