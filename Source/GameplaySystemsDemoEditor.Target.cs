using UnrealBuildTool;
using System.Collections.Generic;

public class GameplaySystemsDemoEditorTarget : TargetRules
{
    public GameplaySystemsDemoEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("GameplaySystemsDemo");
    }
}
