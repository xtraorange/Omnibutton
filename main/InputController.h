#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include "BaseController.h"
#include "input_modules/SerialInputModule.h"

// Use BaseController template to define InputController specifics
class InputController : public BaseController<SerialInputModule> {
public:
    using BaseController::BaseController;  // Inherit constructor
};

#endif