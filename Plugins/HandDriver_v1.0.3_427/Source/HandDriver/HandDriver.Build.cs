// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HandDriver : ModuleRules
{
	public HandDriver(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"LiveLinkInterface",
                "LiveLinkComponents",
                "Messaging",
                
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
                "Engine",
                "InputCore",
                "Json",
                "JsonUtilities",
                "Networking",
                "Slate",
                "SlateCore",
                "Sockets", "LiveLink",
				// ... add private dependencies that you statically link with here ...	
			}
			);
	}
}
