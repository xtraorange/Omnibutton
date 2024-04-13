#ifndef OUTPUT_CONTROLLER_H
#define OUTPUT_CONTROLLER_H

#include "BaseController.h"
#include "output_modules/SerialOutputModule.h"

// Use BaseController template to define OutputController specifics
class OutputController : public BaseController<SerialOutputModule> {
public:
    using BaseController::BaseController;  // Inherit constructor
};

#endif