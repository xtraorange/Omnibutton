#ifndef BASE_MODULE_H
#define BASE_MODULE_H

#include "EventManager.h"
#include "StateManager.h"

class BaseModule {
protected:
    EventManager& eventManager;
    StateManager& stateManager;

public:
    BaseModule(EventManager& evtManager, StateManager& stateMgr)
        : eventManager(evtManager), stateManager(stateMgr) {}

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual ~BaseModule() {}
};

#endif
