#include "State/Button/ReleaseKeyState.h"

#include "Input/Strategy/KeyInputStrategy.h"
#include "State/Button/PressKeyState.h"

ReleaseKeyState::ReleaseKeyState(KeyInputStrategy* buttonInputCommand)
    : _buttonInputCommandStrategy(buttonInputCommand)
{}

void ReleaseKeyState::OnInput()
{
    _buttonInputCommandStrategy->Release();

    _buttonInputCommandStrategy->ChangeState(std::make_unique<PressKeyState>(_buttonInputCommandStrategy));
}