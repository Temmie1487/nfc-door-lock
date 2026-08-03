#pragma once

#include <Arduino.h>

#define RELAY_PIN     13
#define BUTTON_PIN    4
#define MAGNET_PIN    27
#define PN532_RX_PIN  16
#define PN532_TX_PIN  17

#define DOOR_CLOSE_CONFIRM_MS   2000
#define SAFE_TIMEOUT_MS         10000
#define BUTTON_DEBOUNCE_MS      50
#define DOOR_DEBOUNCE_MS        100
#define NFC_COOLDOWN_MS         2000
#define NFC_READ_TIMEOUT_MS     100

struct NFCCard {
    uint8_t uid[7];
    uint8_t length;
};

static const NFCCard authorizedCards[] = {
    {{0x71, 0xA1, 0x2A, 0x6D}, 4},
};

static const int NUM_AUTHORIZED_CARDS = sizeof(authorizedCards) / sizeof(authorizedCards[0]);
