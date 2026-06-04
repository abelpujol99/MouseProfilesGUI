#pragma once
#include "BaseProcessDataStrategy.h"

#include "KeyUsings.h"

class DisplayKey : public BaseProcessDataStrategy<Key>
{
public:

    ~DisplayKey() override = default;

    void StartProcessData() override;

    void StopProcessData() override;

};