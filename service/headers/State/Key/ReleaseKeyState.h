#pragma once
#include "State/Key/IKeyState.h"

class KeyInputStrategy;

class ReleaseKeyState : public IKeyState
{
public:

    ReleaseKeyState(KeyInputStrategy* keyInputStrategy);

    void OnInput(DeviceId deviceId) override;

private:

    KeyInputStrategy* _keyInputStrategy;

};