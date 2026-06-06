#include "MVP/Presenter/BasePresenter.h"

#include "Managers/MVPManager.h"

BasePresenter::BasePresenter() : _serviceModel(MVPManager::GetInstance().GetServiceModel())
{}
