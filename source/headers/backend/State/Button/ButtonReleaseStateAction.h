#pragma once
#include "backend/State/Button/IButtonInputStateAction.h"

class ButtonInputCommandStrategy;

class ButtonReleaseStateAction : public IButtonInputStateAction
{
public:

    ButtonReleaseStateAction(ButtonInputCommandStrategy* buttonInputCommand);

    void OnReceiveInputEvent() override;

private:

    ButtonInputCommandStrategy* _buttonInputCommandStrategy;

};