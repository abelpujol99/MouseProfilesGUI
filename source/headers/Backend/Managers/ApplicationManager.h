#pragma once

#include "Utilities/Observer/ObserverSingleValue.h"

class ApplicationManager
{
public:

    ~ApplicationManager() = default;

    ApplicationManager(const ApplicationManager& other) = delete;
    ApplicationManager& operator=(const ApplicationManager& other) = delete;
    ApplicationManager(ApplicationManager&& other) = delete;
    ApplicationManager& operator=(ApplicationManager&& other) = delete;

    static ApplicationManager& GetInstance();

    void Start();

    std::string GetPathToSwitchScrollMode() const;

    std::weak_ptr<std::function<void(bool)>> SubscribeToShouldRunObserver(std::function<void(bool)> action) const;
    void UnsubscribeToShouldRunObserver(std::weak_ptr<std::function<void(bool)>> action) const;

    void SwitchShouldRun() const;

    bool ShouldRun() const;

    std::weak_ptr<std::function<void(bool)>> SubscribeToShouldGUIRunObserver(std::function<void(bool)> action) const;
    void UnsubscribeToShouldGUIRunObserver(std::weak_ptr<std::function<void(bool)>> action) const;

    void StartGUI();

    void TurnOnGUI() const;

    void TurnOffGUI() const;

private:

    ApplicationManager();

    static std::unique_ptr<ApplicationManager> _applicationManagerInstance;

    std::string _scrollWheelModeHidrawPath;

    std::unique_ptr<ObserverSingleValue<bool>> _shouldRunObserver;

    std::unique_ptr<ObserverSingleValue<bool>> _shouldGUIRunObserver;
};
