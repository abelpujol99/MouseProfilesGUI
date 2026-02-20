#include "backend/State/Button/ButtonPressStateAction.h"

#include "backend/Input/Strategy/ButtonInputCommandStrategy.h"
#include "backend/State/Button/ButtonReleaseStateAction.h"

ButtonPressStateAction::ButtonPressStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommand(buttonInputCommand)
{}

void ButtonPressStateAction::OnReceiveInputEvent()
{
    _buttonInputCommand->Press();
    _buttonInputCommand->DelegateHoldCommand();

    _buttonInputCommand->ChangeState(std::make_unique<ButtonReleaseStateAction>(_buttonInputCommand));
}