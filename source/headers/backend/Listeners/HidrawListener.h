#pragma once
#include "backend/Listeners/BaseListener.h"

class FileCodes;

class HidrawListener : public BaseListener
{
public:

    HidrawListener(FileCodes&& fileCodes);

    void ListenerUpdate() override;

private:

    unsigned short _numberOfInputs;

};