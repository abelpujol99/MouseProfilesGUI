#pragma once

#include "MVP/Model/ServiceModel.h"

class MVPManager
{
public:

    ~MVPManager() = default;

    MVPManager(const MVPManager& other) = delete;
    MVPManager& operator=(const MVPManager& other) = delete;
    MVPManager(MVPManager&& other) = delete;
    MVPManager& operator=(MVPManager&& other) = delete;

    static MVPManager& GetInstance();

    [[nodiscard]] ServiceModel& GetServiceModel();

private:

    MVPManager();

    static std::unique_ptr<MVPManager> _applicationManagerInstance;

    ServiceModel _serviceModel;
};
