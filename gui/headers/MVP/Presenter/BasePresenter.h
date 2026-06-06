#pragma once

#include "MVP/Model/ServiceModel.h"

class BasePresenter
{
public:

    BasePresenter();

    virtual ~BasePresenter() = default;

    virtual void Refresh() = 0;

protected:

    ServiceModel& _serviceModel;
};
