// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Starcel9ServerTarget : TargetRules
{
	public Starcel9ServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new string[] { "Starcel9" }); //, "SlateCore", "Slate", "Text3D" });
		bCompileAgainstEngine = true;
    		//bCompileFreeType = true;
    		//bCompileICU = true;
    
    		// Force link SlateCore
    		bBuildDeveloperTools = true;
	}
}
