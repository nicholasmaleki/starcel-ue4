using UnrealBuildTool;

public class HandDriverGraphNode : ModuleRules
{
    public HandDriverGraphNode(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "AnimationCore",
                "AnimGraphRuntime",
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "LiveLink",
                "LiveLinkInterface",
                "HandDriver",
            }
        );
        
        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd",
                    "Kismet",
                    "AnimGraph",
                    "BlueprintGraph",
                }
            );
        }
    }
}