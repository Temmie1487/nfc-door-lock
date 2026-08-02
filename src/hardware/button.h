#pragma once

#include <Arduino.h>

class Button {
public:
    void begin();
    bool wasPressed();

private:
    bool _lastState = HIGH;
    unsigned long _lastChangeTime = 0;
};
