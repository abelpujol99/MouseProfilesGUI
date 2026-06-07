#pragma once

#include <memory>
#include <fstream>

#include "Serialization/Devices.h"

class SerializationManager
{
public:

    ~SerializationManager() = default;

    SerializationManager(const SerializationManager& other) = delete;
    SerializationManager& operator=(const SerializationManager& other) = delete;
    SerializationManager(SerializationManager&& other) = delete;
    SerializationManager& operator=(SerializationManager&& other) = delete;

    static SerializationManager& GetInstance();

    void SerializeDevices(Devices devices);

    [[nodiscard]] Devices DeserializeDevicesProfiles();

private:

    SerializationManager();

#pragma region Serialization

    void SerializeDeviceProfiles(DeviceProfiles deviceProfiles, std::ofstream& file);

    void SerializeProfile(Profile profile, std::ofstream& file);

    void SerializeSubProfile(SubProfile subProfile, std::ofstream& file);

    void SerializeCodeRemap(CodeRemap codeRemap, std::ofstream& file);

    void SerializeEmitInputEventCommand(std::vector<EmitData> emitsData, std::ofstream& file);

    void SerializeSwitchToSubProfileCommand(uint8_t subProfileIndex, std::ofstream& file);

    void SerializeEmitData(EmitData emitData, std::ofstream& file);

    void SerializeInputEvent(InputEvent inputEvent, std::ofstream& file);

    void SerializeString(const std::string& string, std::ofstream& file);

    template<typename T>
    void SerializePrimitiveType(const T& value, std::ofstream& file);

#pragma endregion

#pragma region Deserialization

    [[nodiscard]] DeviceProfiles DeserializeDeviceProfiles(std::ifstream& file);

    [[nodiscard]] Profile DeserializeProfile(std::ifstream& file);

    [[nodiscard]] SubProfile DeserializeSubProfile(std::ifstream& file);

    [[nodiscard]] CodeRemap DeserializeCodeRemap(std::ifstream& file);

    [[nodiscard]] std::vector<EmitData> DeserializeEmitInputEventCommand(std::ifstream& file);

    [[nodiscard]] uint8_t DeserializeSwitchToSubProfileCommand(std::ifstream& file);

    [[nodiscard]] EmitData DeserializeEmitData(std::ifstream& file);

    [[nodiscard]] InputEvent DeserializeInputEvent(std::ifstream& file);

    [[nodiscard]] std::string DeserializeString(std::ifstream& file);

    template<typename T>
    T DeserializePrimitiveType(std::ifstream& file);

#pragma endregion

    static std::unique_ptr<SerializationManager> _serializationManagerInstance;
};

template <typename T>
void SerializationManager::SerializePrimitiveType(const T& value, std::ofstream& file)
{
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
    file.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
T SerializationManager::DeserializePrimitiveType(std::ifstream& file)
{
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

    T value;

    file.read(reinterpret_cast<char*>(&value), sizeof(T));

    return value;
}