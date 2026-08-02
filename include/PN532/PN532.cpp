#include "PN532.h"

PN532::PN532(PN532Interface &interface) : _interface(interface) {}

void PN532::begin() {}

uint32_t PN532::getFirmwareVersion() {
    return 0;
}

bool PN532::SAMConfig() {
    return true;
}

bool PN532::readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout) {
    (void)cardbaudrate;
    (void)uid;
    (void)uidLength;
    (void)timeout;
    return false;
}
