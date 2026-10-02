#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class ADemoEnemyCharacter;

UCLASS(Blueprintable)
class GAMEPLAYSYSTEMSDEMO_API AWaveManager : public AActor
{
    GENERATED_BODY()

public:
    AWaveManager();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Waves")
    void StartNextWave();

    UFUNCTION(BlueprintPure, Category = "Waves")
    int32 GetCurrentWave() const { return CurrentWave; }

    UFUNCTION(BlueprintPure, Category = "Waves")
    int32 GetAliveEnemyCount() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves")
    TSubclassOf<ADemoEnemyCharacter> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves", meta = (ClampMin = "1"))
    int32 BaseEnemiesPerWave = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves", meta = (ClampMin = "0"))
    int32 AdditionalEnemiesPerWave = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waves", meta = (ClampMin = "0.1"))
    float TimeBetweenWaves = 4.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (ClampMin = "1"))
    int32 MaxSpawnPoints = 12;

private:
    void SpawnWaveEnemies();
    void CheckForWaveClear();
    FVector FindSpawnLocation() const;

    FTimerHandle SpawnTimerHandle;
    FTimerHandle WaveCheckTimerHandle;

    UPROPERTY()
    int32 CurrentWave = 0;

    UPROPERTY()
    int32 PendingSpawns = 0;
};
