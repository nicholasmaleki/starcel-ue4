using UnrealBuildTool;

public class XTensorBridge : ModuleRules
{
	public XTensorBridge(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PCHUsage = PCHUsageMode.NoPCHs;
		bUseUnity = false;
		PublicDefinitions.Add("NOMINMAX");
		PublicDefinitions.Add("BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE=1");
	}
}