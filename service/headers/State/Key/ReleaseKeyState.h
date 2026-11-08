#pragma once
#include "State/Key/IKeyState.h"

class KeyInputStrategy;

class ReleaseKeyState : public IKeyState
{
public:

    ReleaseKeyState(KeyInputStrategy* buttonInputCommand);

    void OnInput() override;

private:

    KeyInputStrategy* _buttonInputCommandStrategy;

};