#pragma once

#include <Arduino.h>

class Relay {
public:
    void begin();
    void unlock();
    void lock();
};
