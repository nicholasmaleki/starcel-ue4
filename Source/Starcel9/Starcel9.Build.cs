using UnrealBuildTool;
using System.IO;

public class Starcel9 : ModuleRules
{
    public Starcel9(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore",
            "HeadMountedDisplay", "SlateCore", "Slate" //, "Text3D"
        });

        //if (Target.Type == TargetType.Server)
        //{
        //    //PublicDefinitions.Add("WITH_FREETYPE=1");
        //    //PublicDefinitions.Add("WITH_HARFBUZZ=1");

        //    PrivateDependencyModuleNames.AddRange(new string[] {
        //    "ApplicationCore",
        //    "RHI",
        //    "RenderCore"
        //});
        //}
        // PrivateDependencyModuleNames.AddRange(new string[]
        // {
        //     "RHI", "RenderCore"
        // });

        // //PublicAdditionalLibraries.Add(ThirdPartyPath);
        // PublicDelayLoadDLLs.Add("harfbuzz.dll");

        // string ThirdPartyPath = Path.Combine(ModuleDirectory, "..", "ThirdParty");
        // string HarfBuzzLib = Path.Combine(ThirdPartyPath, "harfbuzz.lib");

        // //PublicLibraryPaths.Add(ThirdPartyPath);
        // PublicAdditionalLibraries.Add(HarfBuzzLib);
    }
}
