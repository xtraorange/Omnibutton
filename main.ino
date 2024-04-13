#include "EventManager.h"
#include "StateManager.h"
#include "InputController.h"
#include "OutputController.h"
#include "SystemController.h"

EventManager eventManager;
StateManager stateManager;

InputController inputController(eventManager, stateManager);
OutputController outputController(eventManager, stateManager);
SystemController systemController(eventManager, stateManager);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\nDevice initiating");
    inputController.setup();
    outputController.setup();
    systemController.setup();
}

void loop() {
    inputController.loop();
    outputController.loop();
    systemController.loop();
}
