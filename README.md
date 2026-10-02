# UE5 Gameplay Systems Prototype

A C++ gameplay-systems prototype for Unreal Engine 5 demonstrating player input, navigation-based enemy AI, combat, wave spawning and a lightweight UMG HUD.

## Features
- C++ gameplay classes using Character, GameMode and Actor patterns
- Enhanced Input with WASD movement and Space-to-fire
- Nearest-target auto-aim combat
- Navigation-based enemy chasing
- Optional Behavior Tree task for AI extension
- Wave-based enemy spawning with increasing difficulty
- C++ UMG HUD showing health, wave, enemies and score
- Blueprint-friendly properties for meshes, tuning and level dressing

## Build
1. Open `GameplaySystemsDemo.uproject` with UE 5.4+.
2. Generate project files for Visual Studio.
3. Build the Development Editor target.
4. Create/open a map containing a `PlayerStart`, `NavMeshBoundsVolume` and basic obstacles.
5. Set `DemoGameMode` as the map's GameMode Override.
6. Press Play.

## Controls
| Key | Action |
|---|---|
| W / S | Move forward / backward |
| A / D | Strafe left / right |
| Space | Attack nearest enemy |

## Project layout
- `Characters/` - player and enemy gameplay
- `AI/` - navigation controller and Behavior Tree task
- `Game/` - GameMode and wave manager
- `UI/` - C++ UMG HUD

## Notes
The repository intentionally excludes generated Unreal folders such as Binaries, Intermediate, Saved and DerivedDataCache. No custom art assets are required for the C++ systems to compile.
