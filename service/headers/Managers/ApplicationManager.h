#pragma once

#include "Serialization/Devices.h"
#include "Trigger/TriggerBus.h"

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

    static void Shutdown();

    /*void SetEditingDeviceProfiles(std::string deviceName);

    [[nodiscard]] std::string CreateProfile();

    void DeleteProfile(std::string profileName);

    void SetEditingProfile(std::string profileName);

    void CreateSubProfile();

    void DeleteSubProfile(uint8_t index);

    void SetEditingSubProfile(uint8_t index);

    void CreateCodeRemap(Code code, CodeRemap codeRemap);

    void DeleteCodeRemap(Code code);

    [[nodiscard]] std::unordered_map<std::string, Profile> GetDeviceProfiles(std::string deviceName);*/

private:

    ApplicationManager();

    Devices _devices;

    DeviceProfiles* _editingDeviceProfiles {nullptr};

    Profile* _editingProfile {nullptr};

    SubProfile* _editingSubProfile {nullptr};
};