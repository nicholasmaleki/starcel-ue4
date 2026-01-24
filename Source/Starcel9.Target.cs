// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Starcel9Target : TargetRules
{
	public Starcel9Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("Starcel9");

		bCompileAgainstEngine = true;

		// Force enable FreeType and HarfBuzz for Text3D compatibility
		// bCompileFreeType = true;
		// bCompileICU = true;
	}
}
