#pragma once
#include "Listener/BaseListener.h"

class EvdevListener : public BaseListener
{
public:

    EvdevListener(FileCodes&& fileCodes);

    void ListenerUpdate() override;

private:

    int _file;

};