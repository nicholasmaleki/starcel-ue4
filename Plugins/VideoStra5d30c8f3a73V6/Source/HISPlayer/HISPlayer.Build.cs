// Created by HISPlayer � - 2024  

using System.IO;

#if UE_5_0_OR_LATER
using EpicGames.Core;
#else
using Tools.DotNETCommon;
#endif

namespace UnrealBuildTool.Rules
{
    public class HISPlayer : ModuleRules
    {
        public HISPlayer(ReadOnlyTargetRules Target) : base(Target)
        {
            PrecompileForTargets = PrecompileTargetsType.Any;
            PrivatePCHHeaderFile = "Private/HISPlayerPrivatePCH.h";
            
            PublicIncludePaths.AddRange(
            new string[] {
                // ... add public include paths required here ...
            }
            );
            
            PrivateIncludePaths.AddRange(
            new string[] {
                // ... add other private include paths required here ...
            }
            );
            
            PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "RHI",
                "RenderCore",
                "Projects",
                "InputCore",
                "EngineSettings"
                // ... add other public dependencies that you statically link with here ...
            }
            );
            
            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore"
                // ... add private dependencies that you statically link with here ...
            }
            );
            
            DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
            );
            
            PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "Settings",
                "Launch",
            }
            );
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
                string VlcDirectory = Path.Combine(BaseDirectory, "Source", "HISPlayer", "Private", "Libraries", "Windows", Target.Platform.ToString());
                
                Log.TraceInformation("HISPlayerUnrealPlugin: Adding Windows SDK dependency");
                LoadDLL(Path.Combine(VlcDirectory, "HISPlayerWindowsDLL.dll"));
                Log.TraceInformation("HISPlayerUnrealPlugin: Build complete");
            }
            
            else if(Target.Platform == UnrealTargetPlatform.Mac)
            {
                Log.TraceInformation("HISPlayerUnrealPlugin: Adding Mac SDK dependency");
                string MacLibPath = Path.Combine(ModuleDirectory, "Private", "Libraries", "Mac", "libHISPlayerMac.a");
                
                
                string aesLibPath = Path.Combine(ModuleDirectory, "..","ThirdParty", "aes.js");
                
                PublicAdditionalLibraries.Add(MacLibPath);
                if(!Target.bBuildEditor) {
                    
                    if(File.Exists(aesLibPath))
                    {
                        RuntimeDependencies.Add(aesLibPath);
                        CopyFileToBuildDirMac(aesLibPath);
                    }
                    
                    AdditionalBundleResources.Add(new BundleResource(aesLibPath));
                }
                Log.TraceInformation("HISPlayerUnrealPlugin: Build complete");
            }
            
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                Log.TraceInformation("HISPlayerUnrealPlugin: Adding Android SDK dependency");
                string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "HISPlayer_UPL.xml"));
                Log.TraceInformation("HISPlayerUnrealPlugin: Build complete");
            }
            
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                Log.TraceInformation("HISPlayerUnrealPlugin: Adding IOS SDK dependency");
                PublicFrameworks.AddRange(
                new string[]
                {
                    
                    
                });
                
                string IOSLibPath = Path.Combine(ModuleDirectory, "Private", "Libraries", "IOS", "libHISPlayeriOS.a");
                
                // Combine from Source directory to the desired location
                string aesLibPath = Path.Combine(ModuleDirectory, "..","ThirdParty", "aes.js");
                
                if (IOSLibPath != null)
                {
                    PublicAdditionalLibraries.Add(IOSLibPath);
                    
                    if(File.Exists(aesLibPath))
                    {
                        
                        // Add the source file as a runtime dependency
                        RuntimeDependencies.Add(aesLibPath, StagedFileType.NonUFS);
                        AdditionalBundleResources.Add(new BundleResource(aesLibPath));
                    }
                    else {
                        Log.TraceInformation("HISPlayerUnrealPlugin: Cannot find aes.js");
                    }
                }
                Log.TraceInformation("HISPlayerUnrealPlugin: Build complete");
            }
        }
        
        private void CopyFileToBuildDirMac(string FilePath)
        {
            
            string OutputDirectory = Path.Combine(Target.ProjectFile.Directory.FullName, "Binaries", Target.Platform.ToString());
            string ResourceDirectory = Path.Combine(OutputDirectory, Target.Name + ".app", "Contents", "Resources");
            
            if(!Directory.Exists(ResourceDirectory))
            {
                Directory.CreateDirectory(ResourceDirectory);
            }
            
            string Destination = Path.Combine(ResourceDirectory, Path.GetFileName(FilePath));
            
            if(!File.Exists(Destination))
            {
                File.Copy(FilePath, Destination, true);
            }
            
        }
        
        public void LoadDLL(string path)
        {
            if (File.Exists(path))
            {
                RuntimeDependencies.Add(path);
            }
            else
            {
                Log.TraceError("HISPlayerUnrealPlugin: file not found " + path);
            }
        }
    }
}
