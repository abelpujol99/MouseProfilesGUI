#pragma once
#include "backend/Listeners/BaseListener.h"

class EvdevListener : public BaseListener
{

private:

    int _file;

public:

    EvdevListener(FileCodes&& fileCodes);

    void ListenerUpdate() override;

    void CloseFile();
};