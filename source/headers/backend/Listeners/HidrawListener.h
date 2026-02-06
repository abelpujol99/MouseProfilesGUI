#pragma once
#include "backend/Listeners/BaseListener.h"

class FileCodes;

class HidrawListener : public BaseListener
{
private:

    unsigned short _numberOfInputs;

public:

    HidrawListener(FileCodes&& fileCodes);

    void ListenerUpdate() override;
};