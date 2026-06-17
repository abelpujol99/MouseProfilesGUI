#pragma once

class Text;

class BaseProcessDataStrategy
{
public:

    virtual ~BaseProcessDataStrategy() = default;

    void SetText(Text* text);

    virtual void StartProcessData() = 0;

    virtual void StopProcessData() = 0;

protected:

    Text* _text{nullptr};
};
