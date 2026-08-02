#ifndef __PN532_INTERFACE_H__
#define __PN532_INTERFACE_H__

#include <Arduino.h>

class PN532Interface {
public:
    virtual ~PN532Interface() {}
    virtual int8_t writeCommand(const uint8_t *header, uint8_t hlen, const uint8_t *body = 0, uint8_t blen = 0) = 0;
    virtual int16_t readResponse(uint8_t buf[], uint8_t len, uint16_t timeout) = 0;
};

#endif
