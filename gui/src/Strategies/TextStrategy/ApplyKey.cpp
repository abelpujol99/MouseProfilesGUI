#include "Strategies/TextStrategy/ApplyKey.h"

#include "KeyDefines.h"
#include "Managers/Input/TypeManager.h"
#include "UI/Elements/Intermediate/Text.h"

void ApplyKey::StartProcessData()
{
    _onTypingWeakAction = TypeManager::GetInstance().SubscribeToCurrentTypedCharObserver([&](char character) {

        if (character == Backspace)
        {
            _text->EraseLastChar();

            return;
        }

        if (character == Delete)
        {
            _text->ErasePreviousChar();

            return;
        }

        if (character == SpaceBar)
        {
            character = ' ';
        }

        std::string string {character};

        _text->AddText(string);
    });
}

void ApplyKey::StopProcessData()
{
    TypeManager::GetInstance().UnsubscribeToCurrentTypedCharObserver(_onTypingWeakAction);
}