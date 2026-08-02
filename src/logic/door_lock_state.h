#pragma once

class DoorLockState {
public:
    enum State {
        Idle,
        Unlocked,
        DoorOpened,
        DoorClosedConfirm,
        Locking
    };

    void begin();
    void triggerUnlock();
    void update(bool doorIsClosed, unsigned long nowMs);
    State state() const;
    bool isUnlocked() const;

private:
    State _state = Idle;
    bool _doorWasOpened = false;
    unsigned long _unlockStartTime = 0;
    unsigned long _doorClosedStartTime = 0;
};
