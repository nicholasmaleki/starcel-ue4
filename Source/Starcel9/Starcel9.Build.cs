// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Starcel9 : ModuleRules
{
	public Starcel9(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
