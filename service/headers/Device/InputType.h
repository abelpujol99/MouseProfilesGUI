#pragma once

enum class InputType : uint8_t
{
    NONE = 0,
    KEY = 1 << 1,
    RELATIVE = 1 << 2
};

constexpr InputType operator&(InputType lhs, InputType rhs)
{
    return static_cast<InputType>(static_cast<uint8_t>(lhs) &static_cast<uint8_t>(rhs));
}

inline bool HasInputType(const InputType& target, const InputType& type)
{
    return (target & type) != InputType::NONE;
}