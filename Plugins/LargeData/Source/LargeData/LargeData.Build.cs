// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class LargeData : ModuleRules
{
	public LargeData(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDefinitions.Add("UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_2=1");
		CppStandard = CppStandardVersion.Cpp17;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/MPFR/include"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/GMP/include"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/boost/include/"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/xtensor/include"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/hdf5/include/"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/MPFR/lib/mpfr.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/MPFR/lib/mpfr.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/MPFR/lib/mpfr.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/GMP/lib/gmp.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/boost/lib/boost_container-vc142-mt-x64-1_90.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/boost/lib/boost_random-vc142-mt-x64-1_90.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/hdf5/lib/hdf5.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/hdf5/lib/hdf5_hl.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../ThirdParty/hdf5/lib/zlib.lib"));

		string BinPath = Path.Combine(ModuleDirectory, "..", "Binaries", "Win64");

		PublicDelayLoadDLLs.Add("mpfr-6.dll");
		PublicDelayLoadDLLs.Add("gmp-10.dll");
		PublicDelayLoadDLLs.Add("hdf5.dll");
		PublicDelayLoadDLLs.Add("hdf5_hl.dll");
		PublicDelayLoadDLLs.Add("zlib.dll");
		PublicDelayLoadDLLs.Add("aec.dll");

		RuntimeDependencies.Add(
			Path.Combine(BinPath, "mpfr-6.dll")
		);
		RuntimeDependencies.Add(
			Path.Combine(BinPath, "gmp-10.dll")
		);
		RuntimeDependencies.Add(
			Path.Combine(BinPath, "hdf5.dll")
		);
		RuntimeDependencies.Add(
			Path.Combine(BinPath, "hdf5_hl.dll")
		);
		RuntimeDependencies.Add(
			Path.Combine(BinPath, "zlib1.dll")
		);
		RuntimeDependencies.Add(
			Path.Combine(BinPath, "aec.dll")
		);
		
		PublicDefinitions.Add("H5_BUILT_AS_DYNAMIC_LIB");
		PublicDefinitions.Add("H5_USE_18_API");

		bEnableExceptions = true;

		
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Public"),
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "Private"),
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"NetCore",
				"InputCore",
				"RHI",
				"RenderCore"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
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