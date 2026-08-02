#include "door_lock_state.h"
#include "../config.h"

void DoorLockState::begin() {
    _state = Idle;
    _doorWasOpened = false;
    _unlockStartTime = 0;
    _doorClosedStartTime = 0;
}

void DoorLockState::triggerUnlock() {
    if (_state == Unlocked) {
        return;
    }

    _state = Unlocked;
    _doorWasOpened = false;
    _doorClosedStartTime = 0;
    _unlockStartTime = millis();
}

void DoorLockState::update(bool doorIsClosed, unsigned long nowMs) {
    if (_state != Unlocked) {
        return;
    }

    if (!_doorWasOpened) {
        if (!doorIsClosed) {
            _doorWasOpened = true;
            _doorClosedStartTime = 0;
            _state = DoorOpened;
        } else if ((nowMs - _unlockStartTime) >= SAFE_TIMEOUT_MS) {
            _state = Locking;
        }
        return;
    }

    if (doorIsClosed) {
        if (_doorClosedStartTime == 0) {
            _doorClosedStartTime = nowMs;
            _state = DoorClosedConfirm;
        } else if ((nowMs - _doorClosedStartTime) >= DOOR_CLOSE_CONFIRM_MS) {
            _state = Locking;
        }
    } else {
        _doorClosedStartTime = 0;
        _state = DoorOpened;
    }
}

DoorLockState::State DoorLockState::state() const {
    return _state;
}

bool DoorLockState::isUnlocked() const {
    return _state == Unlocked;
}
