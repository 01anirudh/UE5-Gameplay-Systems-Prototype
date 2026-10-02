#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DemoGameMode.generated.h"

UCLASS()
class GAMEPLAYSYSTEMSDEMO_API ADemoGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ADemoGameMode();

    virtual void StartPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetScore() const { return Score; }

    UFUNCTION(BlueprintCallable, Category = "Enemies")
    void NotifyEnemyDefeated();

    UFUNCTION(BlueprintPure, Category = "Enemies")
    int32 GetDefeatedEnemies() const { return DefeatedEnemies; }

private:
    UPROPERTY()
    int32 Score = 0;

    UPROPERTY()
    int32 DefeatedEnemies = 0;
};
