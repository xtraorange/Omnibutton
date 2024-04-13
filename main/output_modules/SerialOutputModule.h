#ifndef SERIAL_OUTPUT_MODULE_H
#define SERIAL_OUTPUT_MODULE_H

#include <Arduino.h>
#include "../BaseModule.h"
#include "../EventManager.h"

class SerialOutputModule : public BaseModule {
public:
    SerialOutputModule(EventManager& evtManager, StateManager& stateMgr)
        : BaseModule(evtManager, stateMgr) {
        // Registering listener for network state change events
        evtManager.registerListener("NETWORK_STATE_CHANGED", [this](std::string data) { this->handleNetworkEvent(data); });
    }

    void initialize() override {
        // Initialization message moved to a central place in main setup to avoid multiple Serial.begin()
        Serial.println("Serial Output Module Initialized");
    }

    void update() override {
        // Output actions are event-driven; no update logic needed.
    }

    void handleNetworkEvent(std::string data) {
        std::string message = "Network status " + data;  // Using std::string's operator+
        Serial.println(message.c_str());  // Convert std::string to const char* with c_str()
    }
};

#endif
