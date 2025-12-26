// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class LWCExtreme : ModuleRules
{
	public LWCExtreme(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/MPFR/include"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/GMP/include"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/boost/include/"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/MPFR/lib/mpfr.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/GMP/lib/gmp.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/boost/lib/boost_container-vc142-mt-x64-1_90.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/boost/lib/boost_random-vc142-mt-x64-1_90.lib"));

		string BinPath = Path.Combine(ModuleDirectory, "..", "Binaries", "Win64");

		PublicDelayLoadDLLs.Add("mpfr-6.dll");
		PublicDelayLoadDLLs.Add("gmp-10.dll");

		RuntimeDependencies.Add(
			Path.Combine(BinPath, "mpfr-6.dll")
		);

		RuntimeDependencies.Add(
			Path.Combine(BinPath, "gmp-10.dll")
		);

		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Public"),
				//Path.Combine(ModuleDirectory, "ThirdParty", "boost"),
				//Path.Combine(ModuleDirectory, "ThirdParty", "mpfr")
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Private"),
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"RHI",
				"RenderCore"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				//"CoreUObject",
				//"Engine",
				//"Slate",
				//"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
