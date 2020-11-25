// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lab3_Xinlin_Gan : ModuleRules
{
	public Lab3_Xinlin_Gan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
