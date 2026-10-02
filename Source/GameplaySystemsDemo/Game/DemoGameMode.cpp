#include "Game/DemoGameMode.h"
#include "Characters/DemoPlayerCharacter.h"
#include "Game/WaveManager.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DemoHUDWidget.h"

ADemoGameMode::ADemoGameMode()
{
    DefaultPawnClass = ADemoPlayerCharacter::StaticClass();
}

void ADemoGameMode::StartPlay()
{
    Super::StartPlay();

    if (!GetWorld())
    {
        return;
    }

    GetWorld()->SpawnActor<AWaveManager>(AWaveManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (UDemoHUDWidget* Widget = CreateWidget<UDemoHUDWidget>(PC, UDemoHUDWidget::StaticClass()))
        {
            Widget->AddToViewport();
        }
    }
}

void ADemoGameMode::AddScore(int32 Amount)
{
    Score = FMath::Max(0, Score + Amount);
}

void ADemoGameMode::NotifyEnemyDefeated()
{
    ++DefeatedEnemies;
    AddScore(100);
}
