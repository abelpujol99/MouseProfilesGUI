#pragma once
#include "Backend/Listener/BaseListener.h"

class HidrawListener : public BaseListener
{
public:

    HidrawListener(FileCodes&& fileCodes);

    void ListenerUpdate() override;

private:

    unsigned short _numberOfInputs;

};