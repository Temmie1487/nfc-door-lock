#pragma once

#include <Arduino.h>
#include "../../include/PN532_HSU/PN532_HSU.h"
#include "../../include/PN532/PN532.h"

class NfcReader {
public:
    void begin();
    bool available() const;
    bool readUid(uint8_t* uid, uint8_t* uidLength, uint16_t timeoutMs);
    bool isAuthorized(const uint8_t* uid, uint8_t uidLength) const;

private:
    HardwareSerial _serial{2};
    PN532_HSU _hsu{_serial};
    PN532 _nfc{_hsu};
    bool _available = false;
};
