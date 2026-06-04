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

    for (auto&& [profileName, profile] : deviceProfiles.profiles)
    {
        SerializeString(profileName, file);
        SerializeProfile(profile, file);
    }
}

void SerializationManager::SerializeProfile(Profile profile, std::ofstream& file)
{
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

    for (auto&& [code, codeRemap] : subProfile.codesRemaps)
    {
        SerializePrimitiveType<Code>(code, file);
        SerializeCodeRemap(codeRemap, file);
    }
}

void SerializationManager::SerializeCodeRemap(CodeRemap codeRemap, std::ofstream& file)
{
    SerializePrimitiveType<CommandType>(codeRemap.commandType, file);

    if (codeRemap.commandType == CommandType::EMIT_INPUT)
    {
        SerializeEmitInputEventCommand(codeRemap.emitsData, file);
    }
    else if (codeRemap.commandType == CommandType::SWITCH_TO_SUB_PROFILE)
    {
        SerializeSwitchToSubProfileCommand(codeRemap.subProfileIndex, file);
    }
}

void SerializationManager::SerializeEmitInputEventCommand(std::vector<EmitData> emitsData, std::ofstream& file)
{
    SerializePrimitiveType<size_t>(emitsData.size(), file);

    for (auto&& emitData : emitsData)
    {
        SerializeEmitData(emitData, file);
    }
}

void SerializationManager::SerializeSwitchToSubProfileCommand(uint8_t subProfileIndex, std::ofstream& file)
{
    SerializePrimitiveType<uint8_t>(subProfileIndex, file);
}

void SerializationManager::SerializeEmitData(EmitData emitData, std::ofstream& file)
{
    SerializePrimitiveType<InputDevices>(emitData.GetInputDevice(), file);
    SerializeInputEvent(emitData.GetInputEvent(), file);
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
        std::string profileName {DeserializeString(file)};
        Profile profile {DeserializeProfile(file)};

        deviceProfiles.profiles.emplace(profileName, profile);
    }

    return deviceProfiles;
}

Profile SerializationManager::DeserializeProfile(std::ifstream& file)
{
    Profile profile{};

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
        Code code {DeserializePrimitiveType<Code>(file)};
        CodeRemap codeRemap {DeserializeCodeRemap(file)};

        subProfile.codesRemaps.emplace(code, codeRemap);
    }

    return subProfile;
}

CodeRemap SerializationManager::DeserializeCodeRemap(std::ifstream& file)
{
    CodeRemap codeRemap{};

    codeRemap.commandType = DeserializePrimitiveType<CommandType>(file);

    if (codeRemap.commandType == CommandType::EMIT_INPUT)
    {
        codeRemap.emitsData = DeserializeEmitInputEventCommand(file);
    }
    else if (codeRemap.commandType == CommandType::SWITCH_TO_SUB_PROFILE)
    {
        codeRemap.subProfileIndex = DeserializeSwitchToSubProfileCommand(file);
    }

    return codeRemap;
}

std::vector<EmitData> SerializationManager::DeserializeEmitInputEventCommand(std::ifstream& file)
{
    std::vector<EmitData> emitsData{};

    size_t emitsDataCount {DeserializePrimitiveType<size_t>(file)};

    emitsData.reserve(emitsDataCount);

    for (size_t i{0}; i < emitsDataCount; ++i)
    {
        emitsData.at(i) = DeserializeEmitData(file);
    }

    return emitsData;
}

uint8_t SerializationManager::DeserializeSwitchToSubProfileCommand(std::ifstream& file)
{
    return DeserializePrimitiveType<uint8_t>(file);
}

EmitData SerializationManager::DeserializeEmitData(std::ifstream& file)
{
    return {DeserializePrimitiveType<InputDevices>(file), DeserializeInputEvent(file)};
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