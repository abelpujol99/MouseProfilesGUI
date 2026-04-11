#pragma once
#include <memory>
#include <functional>

class Text;

template<typename T>
class BaseProcessDataStrategy
{
public:

    virtual ~BaseProcessDataStrategy() = default;

    void SetText(Text* text);

    virtual void StartProcessData() = 0;

    virtual void StopProcessData() = 0;

protected:

    std::weak_ptr<std::function<void(T)>> _onTypingWeakAction;

    Text* _text{nullptr};
};

template<typename T>
void BaseProcessDataStrategy<T>::SetText(Text* text)
{
    _text = text;
}
