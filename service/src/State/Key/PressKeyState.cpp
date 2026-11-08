#include "State/Key/PressKeyState.h"

#include "Input/Strategy/KeyInputStrategy.h"
#include "State/Key/ReleaseKeyState.h"

PressKeyState::PressKeyState(KeyInputStrategy* buttonInputCommand)
    : _buttonInputCommand(buttonInputCommand)
{}

void PressKeyState::OnInput()
{
    _buttonInputCommand->Press();

    _buttonInputCommand->ChangeState(std::make_unique<ReleaseKeyState>(_buttonInputCommand));
}