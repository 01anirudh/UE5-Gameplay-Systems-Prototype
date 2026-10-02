#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoEnemyCharacter.generated.h"

UCLASS(Blueprintable)
class GAMEPLAYSYSTEMSDEMO_API ADemoEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADemoEnemyCharacter();

    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category="Combat")
    float GetHealth() const { return Health; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="1"))
    float MaxHealth = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="1"))
    float ContactDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="0"))
    float ContactDistance = 120.f;

private:
    void TryDamagePlayer();
    void Die();

    UPROPERTY()
    float Health = 100.f;

    FTimerHandle ContactDamageTimerHandle;
};
