#pragma once
#include <memory>

template<typename T>
class IClonable
{
    virtual ~IClonable() = default;

    [[nodiscard]] virtual std::unique_ptr<T> Clone() const = 0;
};
