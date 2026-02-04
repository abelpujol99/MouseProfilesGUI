#pragma once

class IObserver
{

public:

	virtual ~IObserver() = default;

	virtual void UnsubscribeAll() = 0;
};