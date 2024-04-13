#ifndef NETWORK_STATE_MANAGER_H
#define NETWORK_STATE_MANAGER_H

#include <LittleFS.h> // Ensure this library is included for file operations
#include "../StateManager.h"
#include "../EventManager.h" // Include for event management

class NetworkStateManager {
private:
    StateManager& stateManager;
    EventManager& eventManager; // Add EventManager reference

public:
    // Constructor needs both StateManager and EventManager
    NetworkStateManager(StateManager& mgr, EventManager& evtMgr) : stateManager(mgr), eventManager(evtMgr) {}

    NetworkState getCurrentNetworkState() const {
        return stateManager.getNetworkState();
    }

    void updateNetworkState(NetworkState newState) {
        if (stateManager.getNetworkState() != newState) {
            stateManager.updateNetworkState(newState);
            eventManager.fireEvent("NETWORK_STATE_CHANGED", getNetworkStateString());
        }
    }

    std::string getNetworkStateString() const {
        return stateManager.getNetworkStateString();
    }

    NetworkState loadNetworkState() {
        if (LittleFS.exists("/network_state.txt")) {
            File file = LittleFS.open("/network_state.txt", "r");
            if (file) {
                NetworkState state = static_cast<NetworkState>(file.parseInt());
                file.close();
                return state;
            }
        }
        return DISCONNECTED;  // Default state if nothing is saved
    }

    void saveNetworkState(NetworkState state) {
        File file = LittleFS.open("/network_state.txt", "w");
        if (file) {
            file.println(static_cast<int>(state));
            file.close();
        }
    }
};

#endif // NETWORK_STATE_MANAGER_H
