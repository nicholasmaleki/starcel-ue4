#include "Modules/ModuleManager.h"

class FLargeDataModule : public IModuleInterface
{
public:
    virtual void StartupModule() override {}
    virtual void ShutdownModule() override {}
};

IMPLEMENT_MODULE(FLargeDataModule, LargeData)
