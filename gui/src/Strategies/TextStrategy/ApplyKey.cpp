#include "Strategies/TextStrategy/ApplyKey.h"

#include "KeyDefines.h"
#include "Managers/Input/InputManager.h"
#include "UI/Elements/Intermediate/Text.h"

void ApplyKey::StartProcessData()
{
    _onCharPressedAction = InputManager::GetInstance().SubscribeToCharPressed([&](std::string character) {

        if (character == BACKSPACE)
        {
            _text->EraseLastChar();
            return;
        }
        if (character == DELETE)
        {
            _text->ErasePreviousChar();
            return;
        }
        if (character == UP_ARROW)
        {
            //TODO
            return;
        }
        if (character == LEFT_ARROW)
        {
            //TODO
            return;
        }
        if (character == RIGHT_ARROW)
        {
            //TODO
            return;
        }
        if (character == DOWN_ARROW)
        {
            //TODO
            return;
        }
        if (character == HOME)
        {
            //TODO
            return;
        }
        if (character == END)
        {
            //TODO
            return;
        }
        if (character == SPACE_BAR)
        {
            character = ' ';
        }

        std::string string {character};

        _text->AddText(string);
    });
}

void ApplyKey::StopProcessData()
{
    InputManager::GetInstance().UnsubscribeToCharPressed(std::move(_onCharPressedAction));
}