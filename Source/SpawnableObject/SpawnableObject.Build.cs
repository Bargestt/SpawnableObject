// Copyright (C) Vasily Bulgakov. 2022. All Rights Reserved.

using UnrealBuildTool;

public class SpawnableObject : ModuleRules
{
	public SpawnableObject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Public/SpawnableObject.h";

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
            }
			);
		
		
	}
}
