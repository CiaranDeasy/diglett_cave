#include "Tutorial.h"

Tutorial::Tutorial() {
    triggered = false;
}

Tutorial::~Tutorial() {}

bool Tutorial::isTriggered() { return triggered; }
