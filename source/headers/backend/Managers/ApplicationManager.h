#pragma once

#include <forward_list>
#include <thread>

#include <BaseListener.h>

template <typename T>
class ObserverSingleValue;

class ApplicationManager
{

private:

    static std::unique_ptr<ApplicationManager> _applicationManagerInstance;

    std::string _scrollWheelModeHidrawPath;

    std::unique_ptr<ObserverSingleValue<bool>> _shouldRunObserver;

    ApplicationManager();

public:

    ~ApplicationManager() = default;

    ApplicationManager(const ApplicationManager& other) = delete;
    ApplicationManager& operator=(const ApplicationManager& other) = delete;

    static ApplicationManager& GetInstance();

    void Start();

    std::string GetPathToSwitchScrollMode() const;

    std::weak_ptr<std::function<void(bool)>> SubscribeToShouldRunObserver(std::function<void(bool)> action) const;
    void UnsubscribeToShouldRunObserver(std::weak_ptr<std::function<void(bool)>> action) const;

    void SwitchShouldRun() const;
    bool GetShouldRun() const;
};