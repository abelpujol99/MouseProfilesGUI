#pragma once

#include "Serialization/Devices.h"
#include "Observer/ObserverSingleValue.h"

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

    void SetEditingDeviceProfiles(std::string deviceName);

    [[nodiscard]] std::string CreateProfile();

    void DeleteProfile(std::string profileName);

    void SetEditingProfile(std::string profileName);

    void CreateSubProfile();

    void DeleteSubProfile(uint8_t index);

    void SetEditingSubProfile(uint8_t index);

    void CreateCodeRemap(Code code, CodeRemap codeRemap);

    void DeleteCodeRemap(Code code);

    [[nodiscard]] std::unordered_map<std::string, Profile> GetDeviceProfiles(std::string deviceName);

    void StartGUI();

    void TurnOnGUI() const;

    void TurnOffGUI() const;

private:

    ApplicationManager();

    static std::unique_ptr<ApplicationManager> _applicationManagerInstance;

    Devices _devices;

    DeviceProfiles* _editingDeviceProfiles {nullptr};

    Profile* _editingProfile {nullptr};

    SubProfile* _editingSubProfile {nullptr};

    std::string _scrollWheelModeHidrawPath;

    std::unique_ptr<ObserverSingleValue<bool>> _shouldRunObserver;

    std::unique_ptr<ObserverSingleValue<bool>> _shouldGUIRunObserver;
};
