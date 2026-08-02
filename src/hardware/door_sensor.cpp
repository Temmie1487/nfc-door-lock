#include "door_sensor.h"
#include "../config.h"

void DoorSensor::begin() {
    pinMode(MAGNET_PIN, INPUT_PULLUP);
    _lastState = digitalRead(MAGNET_PIN);
    _lastChangeTime = millis();
}

bool DoorSensor::isClosed() {
    bool currentState = (digitalRead(MAGNET_PIN) == HIGH);

    if (currentState != _lastState) {
        _lastChangeTime = millis();
    }

    if ((millis() - _lastChangeTime) < DOOR_DEBOUNCE_MS) {
        return _lastState;
    }

    _lastState = currentState;
    return currentState;
}
