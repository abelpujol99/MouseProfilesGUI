#include "Frontend/UI/Strategies/TextStrategy/ApplyKey.h"

#include "Frontend/KeyDefines.h"
#include "Frontend/Managers/Input/InputManager.h"
#include "Frontend/UI/Basic/Text.h"

void ApplyKey::StartProcessData()
{
    _onTypingWeakAction = InputManager::GetInstance().SubscribeToCurrentTypedCharObserver([&](char character) {

        if (character == Backspace)
        {
            _text->EraseLastChar();

            return;
        }

        std::string string {character};

        _text->AddText(string);
    });
}

void ApplyKey::StopProcessData()
{
    InputManager::GetInstance().UnsubscribeToCurrentTypedCharObserver(_onTypingWeakAction);
}