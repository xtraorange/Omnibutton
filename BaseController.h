#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include "EventManager.h"
#include "StateManager.h"
#include "BaseModule.h"
#include <vector>
#include <memory>

// Macro to simplify module registration in the constructor
#define REGISTER_MODULE(ModuleType) modules.emplace_back(std::make_unique<ModuleType>(eventManager, stateManager))

template<typename... Modules>
class BaseController {
protected:
    EventManager& eventManager;
    StateManager& stateManager;
    std::vector<std::unique_ptr<BaseModule>> modules;

public:
    BaseController(EventManager& evtManager, StateManager& stateMgr)
        : eventManager(evtManager), stateManager(stateMgr) {
        // Initialize modules using pack expansion
        (REGISTER_MODULE(Modules), ...);
    }

    virtual void setup() {
        for (auto& module : modules) {
            module->initialize();
        }
    }

    virtual void loop() {
        for (auto& module : modules) {
            module->update();
        }
    }
};

#endif
