#pragma once

class IReleaseState
{
public:

    virtual ~IReleaseState() = default;

    virtual void Release() = 0;
};