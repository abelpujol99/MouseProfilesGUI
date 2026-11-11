#include "State/Key/PressKeyState.h"

#include "Input/Strategy/KeyInputStrategy.h"
#include "State/Key/ReleaseKeyState.h"

PressKeyState::PressKeyState(KeyInputStrategy* keyInputStrategy) : _keyInputStrategy(keyInputStrategy)
{}

void PressKeyState::OnInput(DeviceId deviceId)
{
    _keyInputStrategy->Press(deviceId);

    _keyInputStrategy->ChangeState(std::make_unique<ReleaseKeyState>(_keyInputStrategy));
}