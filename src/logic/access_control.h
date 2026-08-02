#pragma once

#include <Arduino.h>

class AccessControl {
public:
    bool isAuthorized(const uint8_t* uid, uint8_t uidLength) const;
};
