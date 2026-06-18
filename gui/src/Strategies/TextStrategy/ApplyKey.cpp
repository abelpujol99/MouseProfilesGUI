#include "Strategies/TextStrategy/ApplyKey.h"

#include "KeyDefines.h"
#include "Managers/Input/InputManager.h"
#include "../../../headers/UI/Elements/Intermediate/Text.h"

ApplyKey::ApplyKey()
{
    /*_charPressedActions.emplace(BACKSPACE, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(DELETE, [&](){_text->ErasePreviousChar();});
    _charPressedActions.emplace(UP_ARROW, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(LEFT_ARROW, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(RIGHT_ARROW, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(DOWN_ARROW, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(HOME, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(END, [&](){_text->EraseLastChar();});
    _charPressedActions.emplace(SPACE_BAR, [&](){_text->AddText(" ");});*/
}

void ApplyKey::StartProcessData()
{
    _onCharPressedAction = InputManager::GetInstance().SubscribeToCharPressed([&](std::string character) {

        if (_charPressedActions.contains(character))
        {
            _charPressedActions.at(character)();
            return;
        }

        //_text->AddText(character);
    });
}

void ApplyKey::StopProcessData()
{
    InputManager::GetInstance().UnsubscribeToCharPressed(std::move(_onCharPressedAction));
}