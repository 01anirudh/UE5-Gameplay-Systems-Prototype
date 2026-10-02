#include "AI/BTTask_ChasePlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
    NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8*)
{
    AAIController* AI = OwnerComp.GetAIOwner();
    APawn* Player = AI ? UGameplayStatics::GetPlayerPawn(AI->GetWorld(), 0) : nullptr;
    if (!AI || !Player)
    {
        return EBTNodeResult::Failed;
    }

    AI->MoveToActor(Player, AcceptanceRadius);
    return EBTNodeResult::Succeeded;
}
