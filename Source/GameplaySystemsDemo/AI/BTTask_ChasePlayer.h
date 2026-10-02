#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChasePlayer.generated.h"

UCLASS()
class GAMEPLAYSYSTEMSDEMO_API UBTTask_ChasePlayer : public UBTTaskNode
{
    GENERATED_BODY()
public:
    UBTTask_ChasePlayer();
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UPROPERTY(EditAnywhere, Category="AI")
    float AcceptanceRadius = 110.f;
};
