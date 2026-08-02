#include <Arduino.h>
#include "config.h"
#include "hardware/relay.h"
#include "hardware/button.h"
#include "hardware/door_sensor.h"
#include "hardware/nfc.h"
#include "hardware/logger.h"
#include "logic/door_lock_state.h"
#include "logic/access_control.h"

Relay relay;
Button button;
DoorSensor doorSensor;
NfcReader nfc;
DoorLockState lockState;
AccessControl accessControl;

unsigned long lastNFCReadTime = 0;

void setup() {
    Logger::init();
    delay(500);

    Logger::println("");
    Logger::println("========================================");
    Logger::println("  NFC Smart Door Lock System (HSU Mode)");
    Logger::println("========================================");

    relay.begin();
    button.begin();
    doorSensor.begin();
    nfc.begin();
    lockState.begin();

    Logger::println("[INIT] GPIO configured.");
    Logger::printf("[INIT] Door sensor: %s\n", doorSensor.isClosed() ? "CLOSED" : "OPEN");
    Logger::println("[INIT] System ready.");
}

void loop() {
    if (button.wasPressed()) {
        Logger::println("[INPUT] Button pressed.");
        lockState.triggerUnlock();
        relay.unlock();
    }

    if (nfc.available()) {
        if ((millis() - lastNFCReadTime) >= NFC_COOLDOWN_MS) {
            uint8_t uid[7] = {0};
            uint8_t uidLength = 0;

            bool success = nfc.readUid(uid, &uidLength, NFC_READ_TIMEOUT_MS);
            if (success && uidLength > 0) {
                lastNFCReadTime = millis();

                Logger::printf("[INPUT] NFC card detected. Length=%d, UID=", uidLength);
                for (uint8_t i = 0; i < uidLength; i++) {
                    Logger::printf("%02X", uid[i]);
                    if (i < uidLength - 1) Logger::print(":");
                }
                Logger::println("");

                if (accessControl.isAuthorized(uid, uidLength)) {
                    Logger::println("[AUTH] >>> ACCESS GRANTED <<<");
                    lockState.triggerUnlock();
                    relay.unlock();
                } else {
                    Logger::println("[AUTH] Access DENIED. Unknown card.");
                }
            }
        }
    }

    if (lockState.isUnlocked()) {
        bool doorIsClosed = doorSensor.isClosed();
        lockState.update(doorIsClosed, millis());

        if (lockState.state() == DoorLockState::Locking) {
            Logger::println("[ACTION] === LOCK === Relay OFF (LOW)");
            relay.lock();
            lockState.begin();
        }
    }

    delay(10);
}
