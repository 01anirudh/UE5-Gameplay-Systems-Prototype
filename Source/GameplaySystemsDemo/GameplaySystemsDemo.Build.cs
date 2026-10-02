using UnrealBuildTool;

public class GameplaySystemsDemo : ModuleRules
{
    public GameplaySystemsDemo(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "NavigationSystem",
            "GameplayTasks",
            "UMG"
        });
    }
}
