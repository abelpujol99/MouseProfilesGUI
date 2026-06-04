#pragma once

template<typename T>
concept Pointer = requires(T ptr)
{
    {*ptr};
    {ptr == nullptr};
    {static_cast<bool>(ptr)};
};