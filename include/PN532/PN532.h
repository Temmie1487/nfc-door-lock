#ifndef __PN532_H__
#define __PN532_H__

#include <Arduino.h>
#include "PN532/PN532Interface.h"

#define PN532_PREAMBLE 0x00
#define PN532_STARTCODE1 0x00
#define PN532_STARTCODE2 0xFF
#define PN532_HOSTTOPN532 0xD4
#define PN532_PN532TOHOST 0xD5
#define PN532_POSTAMBLE 0x00

#define PN532_TIMEOUT 0x01
#define PN532_INVALID_FRAME 0x02
#define PN532_NO_SPACE 0x03
#define PN532_INVALID_ACK 0x04
#define PN532_ACK_WAIT_TIME 0x0A

#define PN532_MIFARE_ISO14443A 0x00

class PN532 {
public:
    explicit PN532(PN532Interface &interface);
    void begin();
    uint32_t getFirmwareVersion();
    bool SAMConfig();
    bool readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout = 1000);

private:
    PN532Interface &_interface;
};

#endif
