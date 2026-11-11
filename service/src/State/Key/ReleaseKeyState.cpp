#include "State/Key/ReleaseKeyState.h"

#include "Input/Strategy/KeyInputStrategy.h"
#include "State/Key/PressKeyState.h"

ReleaseKeyState::ReleaseKeyState(KeyInputStrategy* keyInputStrategy) : _keyInputStrategy(keyInputStrategy)
{}

void ReleaseKeyState::OnInput(DeviceId deviceId)
{
    _keyInputStrategy->Release(deviceId);

    _keyInputStrategy->ChangeState(std::make_unique<PressKeyState>(_keyInputStrategy));
}