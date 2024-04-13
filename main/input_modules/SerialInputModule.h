#ifndef SERIAL_INPUT_MODULE_H
#define SERIAL_INPUT_MODULE_H

#include "../BaseModule.h"
#include <Arduino.h> // Include Arduino standard library for serial functions

class SerialInputModule : public BaseModule {
public:
    SerialInputModule(EventManager& evtManager, StateManager& stateMgr)
        : BaseModule(evtManager, stateMgr) {}

    void initialize() override {
        // Initialization message moved to a central place in main setup to avoid multiple Serial.begin()
        Serial.println("Serial Input Module Initialized");
    }

    void update() override {
        if (Serial.available() > 0) {
            String input = Serial.readStringUntil('\n'); // Read the input until newline
            input.trim(); // Remove any whitespace or newline characters
            if (!input.isEmpty()) {
                // Fire an event with the name exactly matching the input string
                eventManager.fireEvent(input.c_str(), "Triggered by Serial Input");
            }
        }
    }
};

#endif
