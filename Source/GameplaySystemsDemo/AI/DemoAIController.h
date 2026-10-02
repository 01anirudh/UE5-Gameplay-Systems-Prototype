#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DemoAIController.generated.h"

class UBehaviorTree;

UCLASS()
class GAMEPLAYSYSTEMSDEMO_API ADemoAIController : public AAIController
{
    GENERATED_BODY()

public:
    ADemoAIController();

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float AcceptanceRadius = 110.f;

private:
    void ChasePlayer();
    FTimerHandle ChaseTimerHandle;
};
