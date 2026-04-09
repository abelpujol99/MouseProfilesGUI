#include "Backend/State/Button/ButtonPressStateAction.h"

#include "Backend/Input/Strategy/ButtonInputCommandStrategy.h"
#include "Backend/State/Button/ButtonReleaseStateAction.h"

ButtonPressStateAction::ButtonPressStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommand(buttonInputCommand)
{}

void ButtonPressStateAction::OnReceiveInputEvent()
{
    _buttonInputCommand->Press();
    _buttonInputCommand->DelegateHoldCommand();

    _buttonInputCommand->ChangeState(std::make_unique<ButtonReleaseStateAction>(_buttonInputCommand));
}