#pragma once

#include "Modules/ModuleManager.h"

class FLWCExtremeModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
