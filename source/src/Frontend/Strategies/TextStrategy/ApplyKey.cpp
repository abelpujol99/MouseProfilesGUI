#include "Frontend/Strategies/TextStrategy/ApplyKey.h"

#include "Frontend/KeyDefines.h"
#include "Frontend/Managers/Input/TypeManager.h"
#include "Frontend/UI/Elements/Intermediate/Text.h"

void ApplyKey::StartProcessData()
{
    _onTypingWeakAction = TypeManager::GetInstance().SubscribeToCurrentTypedCharObserver([&](char character) {

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
    TypeManager::GetInstance().UnsubscribeToCurrentTypedCharObserver(_onTypingWeakAction);
}