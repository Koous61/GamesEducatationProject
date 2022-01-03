// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lesson15 : ModuleRules
{
	public Lesson15(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
