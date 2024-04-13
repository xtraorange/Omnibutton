#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "BaseController.h"
#include "system_modules/NetworkModule.h"

// Use BaseController template to define SystemController specifics
class SystemController : public BaseController<NetworkModule> {
public:
    using BaseController::BaseController;  // Inherit constructor
};

#endif
