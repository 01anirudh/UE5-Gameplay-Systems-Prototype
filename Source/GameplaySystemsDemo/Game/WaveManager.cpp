#include "Game/WaveManager.h"
#include "Characters/DemoEnemyCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "NavigationSystem.h"

AWaveManager::AWaveManager()
{
    PrimaryActorTick.bCanEverTick = false;
    EnemyClass = ADemoEnemyCharacter::StaticClass();
}

void AWaveManager::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveManager::StartNextWave, 2.f, false);
    GetWorldTimerManager().SetTimer(WaveCheckTimerHandle, this, &AWaveManager::CheckForWaveClear, 1.f, true);
}

void AWaveManager::StartNextWave()
{
    ++CurrentWave;
    PendingSpawns = BaseEnemiesPerWave + (CurrentWave - 1) * AdditionalEnemiesPerWave;
    SpawnWaveEnemies();
}

void AWaveManager::SpawnWaveEnemies()
{
    if (!EnemyClass || PendingSpawns <= 0)
    {
        return;
    }

    while (PendingSpawns > 0)
    {
        const FVector Location = FindSpawnLocation();
        GetWorld()->SpawnActor<ADemoEnemyCharacter>(EnemyClass, Location, FRotator::ZeroRotator);
        --PendingSpawns;
    }
}

int32 AWaveManager::GetAliveEnemyCount() const
{
    int32 Count = 0;
    for (TActorIterator<ADemoEnemyCharacter> It(GetWorld()); It; ++It)
    {
        if (IsValid(*It) && !It->IsActorBeingDestroyed())
        {
            ++Count;
        }
    }
    return Count;
}

void AWaveManager::CheckForWaveClear()
{
    if (CurrentWave == 0 || PendingSpawns > 0)
    {
        return;
    }

    if (GetAliveEnemyCount() == 0 && !GetWorldTimerManager().IsTimerActive(SpawnTimerHandle))
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveManager::StartNextWave, TimeBetweenWaves, false);
    }
}

FVector AWaveManager::FindSpawnLocation() const
{
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    const FVector PlayerLocation = Player ? Player->GetActorLocation() : FVector::ZeroVector;

    const float Angle = FMath::FRandRange(0.f, 2.f * PI);
    const float Radius = FMath::FRandRange(900.f, 1300.f);
    const FVector Desired = PlayerLocation + FVector(FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius, 100.f);

    if (UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
    {
        FNavLocation Projected;
        if (NavSystem->ProjectPointToNavigation(Desired, Projected, FVector(250.f, 250.f, 350.f)))
        {
            return Projected.Location;
        }
    }

    return Desired;
}
