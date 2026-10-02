#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "DemoPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
class ADemoEnemyCharacter;

UCLASS(Blueprintable)
class GAMEPLAYSYSTEMSDEMO_API ADemoPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADemoPlayerCharacter();

    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category="Combat")
    float GetHealth() const { return Health; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="1"))
    float MaxHealth = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="1"))
    float FireDamage = 35.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="0.05"))
    float FireCooldown = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="100"))
    float AutoAimRadius = 1500.f;

private:
    void MoveForward(const FInputActionValue& Value, float Scale);
    void MoveRight(const FInputActionValue& Value, float Scale);
    void Fire();
    AActor* FindNearestEnemy() const;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY()
    TObjectPtr<UInputMappingContext> MappingContext;

    UPROPERTY()
    TObjectPtr<UInputAction> ForwardAction;

    UPROPERTY()
    TObjectPtr<UInputAction> BackAction;

    UPROPERTY()
    TObjectPtr<UInputAction> RightAction;

    UPROPERTY()
    TObjectPtr<UInputAction> LeftAction;

    UPROPERTY()
    TObjectPtr<UInputAction> FireAction;

    float Health = 100.f;
    bool bFireOnCooldown = false;
};
