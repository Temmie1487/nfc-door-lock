#include "button.h"
#include "../config.h"

void Button::begin() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    _lastState = digitalRead(BUTTON_PIN);
    _lastChangeTime = millis();
}

bool Button::wasPressed() {
    bool currentState = digitalRead(BUTTON_PIN);

    if (currentState != _lastState) {
        _lastChangeTime = millis();
    }

    if ((millis() - _lastChangeTime) >= BUTTON_DEBOUNCE_MS) {
        if (currentState == LOW && _lastState == HIGH) {
            _lastState = currentState;
            return true;
        }
        _lastState = currentState;
    }

    return false;
}
