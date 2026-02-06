#pragma once

#include <functional>

class IObserver
{

public:

	virtual ~IObserver() = default;

	virtual void UnsubscribeAll() = 0;
};