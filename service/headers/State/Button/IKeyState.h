#pragma once

class IKeyState
{
public:

    virtual ~IKeyState() = default;

    virtual void OnInput() = 0;
};
