#pragma once

#include <Arduino.h>

class DoorSensor {
public:
    void begin();
    bool isClosed();

private:
    bool _lastState = HIGH;
    unsigned long _lastChangeTime = 0;
};
