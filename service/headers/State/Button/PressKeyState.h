#pragma once
#include "State/Button/IKeyState.h"

class KeyInputStrategy;

class PressKeyState : public IKeyState
{
public:

    PressKeyState(KeyInputStrategy* buttonInputCommand);

    void OnInput() override;

private:

    KeyInputStrategy* _buttonInputCommand;

};