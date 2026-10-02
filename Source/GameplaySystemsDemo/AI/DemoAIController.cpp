#include "AI/DemoAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

ADemoAIController::ADemoAIController()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADemoAIController::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(ChaseTimerHandle, this, &ADemoAIController::ChasePlayer, 0.25f, true);
}

void ADemoAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if (BehaviorTreeAsset)
    {
        RunBehaviorTree(BehaviorTreeAsset);
    }
}

void ADemoAIController::ChasePlayer()
{
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player && GetPawn())
    {
        MoveToActor(Player, AcceptanceRadius);
    }
}
