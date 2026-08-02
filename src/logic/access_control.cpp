#include "access_control.h"
#include "../config.h"

bool AccessControl::isAuthorized(const uint8_t* uid, uint8_t uidLength) const {
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
