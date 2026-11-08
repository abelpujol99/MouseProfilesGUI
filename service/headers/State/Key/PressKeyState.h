#pragma once
#include "State/Key/IKeyState.h"

class KeyInputStrategy;

class PressKeyState : public IKeyState
{
public:

    PressKeyState(KeyInputStrategy* buttonInputCommand);

    void OnInput() override;

private:

    KeyInputStrategy* _buttonInputCommand;

};