#pragma once

class IInputState
{
public:

     virtual ~IInputState() = default;

     virtual void Start() = 0;

     virtual void End() = 0;
};