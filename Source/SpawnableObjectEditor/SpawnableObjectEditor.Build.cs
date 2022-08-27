// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

using UnrealBuildTool;

public class SpawnableObjectEditor : ModuleRules
{
	public SpawnableObjectEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
				
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"SpawnableObject",

				"CoreUObject",
				"Engine",
				"DeveloperSettings",

				"PropertyEditor",
				"UnrealEd",
								
			
			}
			);
		
	}
}
