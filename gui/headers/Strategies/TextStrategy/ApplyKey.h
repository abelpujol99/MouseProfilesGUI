#pragma once
#include "BaseProcessDataStrategy.h"

class ApplyKey : public BaseProcessDataStrategy<char>
{
public:

    ~ApplyKey() override = default;

    void StartProcessData() override;

    void StopProcessData() override;

};