#pragma once
#include <IButtonInputStateAction.h>

class ButtonInputCommandStrategy;

class ButtonReleaseStateAction : public IButtonInputStateAction
{
private:

    ButtonInputCommandStrategy* _buttonInputCommandStrategy;

public:

    ButtonReleaseStateAction(ButtonInputCommandStrategy* buttonInputCommand);

    void OnReceiveInputEvent() override;

};