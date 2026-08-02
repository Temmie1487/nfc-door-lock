#include "relay.h"
#include "../config.h"

void Relay::begin() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

void Relay::unlock() {
    digitalWrite(RELAY_PIN, HIGH);
}

void Relay::lock() {
    digitalWrite(RELAY_PIN, LOW);
}
