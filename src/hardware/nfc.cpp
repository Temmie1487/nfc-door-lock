#include "nfc.h"
#include "../config.h"

void NfcReader::begin() {
    _serial.begin(115200, SERIAL_8N1, PN532_RX_PIN, PN532_TX_PIN);
    _nfc.begin();
    uint32_t versiondata = _nfc.getFirmwareVersion();

    if (!versiondata) {
        Serial.println("[ERROR] PN532 not detected! Check HSU wiring and mode switch.");
        _available = false;
    } else {
        Serial.printf("[INIT] PN532 OK. Firmware: 0x%08lX\n", (unsigned long)versiondata);
        _nfc.SAMConfig();
        _available = true;
    }
}

bool NfcReader::available() const {
    return _available;
}

bool NfcReader::readUid(uint8_t* uid, uint8_t* uidLength, uint16_t timeoutMs) {
    return _nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, uidLength, timeoutMs);
}

bool NfcReader::isAuthorized(const uint8_t* uid, uint8_t uidLength) const {
    for (int i = 0; i < NUM_AUTHORIZED_CARDS; i++) {
        if (uidLength != authorizedCards[i].length) {
            continue;
        }

        bool match = true;
        for (uint8_t j = 0; j < uidLength; j++) {
            if (uid[j] != authorizedCards[i].uid[j]) {
                match = false;
                break;
            }
        }

        if (match) {
            return true;
        }
    }

    return false;
}
