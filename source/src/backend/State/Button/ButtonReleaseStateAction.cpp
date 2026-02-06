#include "backend/State/Button/ButtonReleaseStateAction.h"

#include "backend/Input/Strategies/ButtonInputCommandStrategy.h"
#include "backend/State/Button/ButtonPressStateAction.h"

ButtonReleaseStateAction::ButtonReleaseStateAction(ButtonInputCommandStrategy* buttonInputCommand)
    : _buttonInputCommandStrategy(buttonInputCommand)
{}

void ButtonReleaseStateAction::OnReceiveInputEvent()
{
    _buttonInputCommandStrategy->SwitchToOffState();

    _buttonInputCommandStrategy->ChangeState(std::make_unique<ButtonPressStateAction>(_buttonInputCommandStrategy));
}