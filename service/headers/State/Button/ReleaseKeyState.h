#pragma once
#include "State/Button/IKeyState.h"

class KeyInputStrategy;

class ReleaseKeyState : public IKeyState
{
public:

    ReleaseKeyState(KeyInputStrategy* buttonInputCommand);

    void OnInput() override;

private:

    KeyInputStrategy* _buttonInputCommandStrategy;

};