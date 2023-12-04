// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tactical_TriumphEditorTarget : TargetRules
{
	public Tactical_TriumphEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("Tactical_Triumph");
	}
}