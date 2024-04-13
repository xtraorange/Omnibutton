#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <string>

enum NetworkState {
    DISCONNECTED,
    CONNECTING,
    HUB_NETWORK,
    CUSTOM_NETWORK,
    CAPTIVE_PORTAL
};

class StateManager {
private:
    NetworkState networkState;

public:
    StateManager() : networkState(DISCONNECTED) {}

    void updateNetworkState(NetworkState newState) {
        if (networkState != newState) {
            networkState = newState;
        }
    }

    NetworkState getNetworkState() const {
        return networkState;
    }

    std::string getNetworkStateString() const {
        switch (networkState) {  // Correct variable name used
            case DISCONNECTED: return "DISCONNECTED";
            case CONNECTING: return "CONNECTING";
            case HUB_NETWORK: return "HUB_NETWORK";
            case CUSTOM_NETWORK: return "CUSTOM_NETWORK";
            case CAPTIVE_PORTAL: return "CAPTIVE_PORTAL";
            default: return "UNKNOWN_STATE";
        }
    }
};

#endif // STATE_MANAGER_H
