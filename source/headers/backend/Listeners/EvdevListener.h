#pragma once
#include "backend/Listeners/BaseListener.h"

class EvdevListener : public BaseListener
{
public:

    EvdevListener(FileCodes&& fileCodes);

    void ListenerUpdate() override;

    void CloseFile();

private:

    int _file;

};