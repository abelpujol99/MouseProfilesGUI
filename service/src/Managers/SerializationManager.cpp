#include "Managers/SerializationManager.h"

#include <filesystem>

#define SERIALIZATION_PATH "serialization/data.bin"

std::unique_ptr<SerializationManager> SerializationManager::_serializationManagerInstance {nullptr};

SerializationManager::SerializationManager()
{
}

SerializationManager& SerializationManager::GetInstance()
{
    if (_serializationManagerInstance == nullptr)
    {
        _serializationManagerInstance.reset(new SerializationManager());
    }

    return *_serializationManagerInstance;
}

#pragma region Serialization

void SerializationManager::SerializeDevices(Devices devices)
{
    const std::filesystem::path resourceDir {RESOURCE_DIR};

    const std::filesystem::path path {resourceDir / SERIALIZATION_PATH};

    std::ofstream file {path, std::ios::binary};

    if (!file.is_open())
    {
        throw "Failed to open file to write";
    }

    SerializePrimitiveType<size_t>(devices.devicesProfiles.size(), file);

    for (auto&& [deviceName, deviceProfiles] : devices.devicesProfiles)
    {
        if (deviceProfiles.profiles.empty())
        {
            continue;
        }

        SerializeString(deviceName, file);

        SerializeDeviceProfiles(deviceProfiles, file);
    }

    file.close();
}

void SerializationManager::SerializeDeviceProfiles(DeviceProfiles deviceProfiles, std::ofstream& file)
{
    SerializePrimitiveType<size_t>(deviceProfiles.profiles.size(),file);

    for (auto&& profile : deviceProfiles.profiles)
    {
        SerializeProfile(profile, file);
    }
}

void SerializationManager::SerializeProfile(Profile profile, std::ofstream& file)
{
    SerializeString(profile.name, file);
    SerializePrimitiveType<bool>(profile.isCurrentProfile, file);
    SerializePrimitiveType<size_t>(profile.subProfiles.size(), file);

    for (auto&& subProfile : profile.subProfiles)
    {
        SerializeSubProfile(subProfile, file);
    }
}

void SerializationManager::SerializeSubProfile(SubProfile subProfile, std::ofstream& file)
{
    SerializePrimitiveType<size_t>(subProfile.codesRemaps.size(), file);

    for (auto&& codeRemap : subProfile.codesRemaps)
    {
        SerializeCodeRemap(codeRemap, file);
    }
}

void SerializationManager::SerializeCodeRemap(CodeRemap codeRemap, std::ofstream& file)
{
    SerializePrimitiveType<Code>(codeRemap.code, file);
    SerializePrimitiveType<CommandType>(codeRemap.commandType, file);

    if (codeRemap.commandType == CommandType::EMIT_INPUT)
    {
        SerializeEmitInputEventCommand(codeRemap.inputEvents, file);
    }
    else if (codeRemap.commandType == CommandType::SWITCH_TO_SUB_PROFILE)
    {
        SerializeSwitchToSubProfileCommand(codeRemap.subProfileIndex, file);
    }
}

void SerializationManager::SerializeEmitInputEventCommand(std::vector<InputEvent> inputEvents, std::ofstream& file)
{
    SerializePrimitiveType<size_t>(inputEvents.size(), file);

    for (auto&& inputEvent : inputEvents)
    {
        SerializeInputEvent(inputEvent, file);
    }
}

void SerializationManager::SerializeSwitchToSubProfileCommand(uint8_t subProfileIndex, std::ofstream& file)
{
    SerializePrimitiveType<uint8_t>(subProfileIndex, file);
}

void SerializationManager::SerializeInputEvent(InputEvent inputEvent, std::ofstream& file)
{
    SerializePrimitiveType<unsigned short>(inputEvent.GetType(), file);
    SerializePrimitiveType<Code>(inputEvent.GetCode(), file);
    SerializePrimitiveType<int>(inputEvent.GetValue(), file);
}

void SerializationManager::SerializeString(const std::string& string, std::ofstream& file)
{
    const size_t stringLength {string.length()};

    file.write(reinterpret_cast<const char*>(&stringLength), sizeof(size_t));
    file.write(string.data(), stringLength);
}

#pragma endregion

#pragma region Deserialization

Devices SerializationManager::DeserializeDevicesProfiles()
{
    const std::filesystem::path resourceDir {RESOURCE_DIR};

    const std::filesystem::path path {resourceDir / SERIALIZATION_PATH};

    std::ifstream file {path, std::ios::binary};

    if (!file.is_open())
    {
        return {};
    }

    Devices devices{};

    size_t devicesCount {DeserializePrimitiveType<size_t>(file)};

    for (size_t i{0}; i < devicesCount; ++i)
    {
        std::string deviceName {DeserializeString(file)};

        DeviceProfiles deviceProfiles {DeserializeDeviceProfiles(file)};

        devices.devicesProfiles.emplace(deviceName, deviceProfiles);
    }

    file.close();

    return devices;
}

DeviceProfiles SerializationManager::DeserializeDeviceProfiles(std::ifstream& file)
{
    DeviceProfiles deviceProfiles{};

    size_t profilesCount {DeserializePrimitiveType<size_t>(file)};

    for (size_t j{0}; j < profilesCount; ++j)
    {
        Profile profile {DeserializeProfile(file)};

        deviceProfiles.profiles.push_back(profile);
    }

    return deviceProfiles;
}

Profile SerializationManager::DeserializeProfile(std::ifstream& file)
{
    Profile profile{};

    profile.name = DeserializeString(file);
    profile.isCurrentProfile = DeserializePrimitiveType<bool>(file);
    size_t subProfilesCount {DeserializePrimitiveType<size_t>(file)};

    for (size_t i{0}; i < subProfilesCount; ++i)
    {
        profile.subProfiles.push_back(DeserializeSubProfile(file));
    }

    return profile;
}

SubProfile SerializationManager::DeserializeSubProfile(std::ifstream& file)
{
    SubProfile subProfile{};

    size_t codesRemapsCount {DeserializePrimitiveType<size_t>(file)};

    for (size_t i{0}; i < codesRemapsCount; ++i)
    {
        CodeRemap codeRemap {DeserializeCodeRemap(file)};

        subProfile.codesRemaps.push_back(codeRemap);
    }

    return subProfile;
}

CodeRemap SerializationManager::DeserializeCodeRemap(std::ifstream& file)
{
    CodeRemap codeRemap{};

    codeRemap.code = DeserializePrimitiveType<Code>(file);
    codeRemap.commandType = DeserializePrimitiveType<CommandType>(file);

    if (codeRemap.commandType == CommandType::EMIT_INPUT)
    {
        codeRemap.inputEvents = DeserializeEmitInputEventCommand(file);
    }
    else if (codeRemap.commandType == CommandType::SWITCH_TO_SUB_PROFILE)
    {
        codeRemap.subProfileIndex = DeserializeSwitchToSubProfileCommand(file);
    }

    return codeRemap;
}

std::vector<InputEvent> SerializationManager::DeserializeEmitInputEventCommand(std::ifstream& file)
{
    std::vector<InputEvent> inputEvents{};

    size_t emitsDataCount {DeserializePrimitiveType<size_t>(file)};

    inputEvents.reserve(emitsDataCount);

    for (size_t i{0}; i < emitsDataCount; ++i)
    {
        inputEvents.at(i) = DeserializeInputEvent(file);
    }

    return inputEvents;
}

uint8_t SerializationManager::DeserializeSwitchToSubProfileCommand(std::ifstream& file)
{
    return DeserializePrimitiveType<uint8_t>(file);
}

InputEvent SerializationManager::DeserializeInputEvent(std::ifstream& file)
{
    return {DeserializePrimitiveType<unsigned short>(file),
        DeserializePrimitiveType<Code>(file),
        DeserializePrimitiveType<int>(file)};
}

std::string SerializationManager::DeserializeString(std::ifstream& file)
{
    size_t stringLength {0};
    file.read(reinterpret_cast<char*>(&stringLength), sizeof(size_t));

    std::string string(stringLength, '\0');
    file.read(string.data(), stringLength);

    return string;
}

#pragma endregion