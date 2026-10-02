#include "UI/DemoHUDWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Characters/DemoPlayerCharacter.h"
#include "Game/DemoGameMode.h"
#include "Game/WaveManager.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void UDemoHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    RootCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootCanvas"));
    WidgetTree->RootWidget = RootCanvas;

    StatusText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Status"));
    StatusText->SetText(FText::FromString(TEXT("Initializing...")));
    if (UCanvasPanelSlot* Slot = RootCanvas->AddChildToCanvas(StatusText))
    {
        Slot->SetPosition(FVector2D(32.f, 28.f));
        Slot->SetAutoSize(true);
    }

    ControlsText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("Controls"));
    ControlsText->SetText(FText::FromString(TEXT("WASD Move | SPACE Fire")));
    if (UCanvasPanelSlot* Slot = RootCanvas->AddChildToCanvas(ControlsText))
    {
        Slot->SetAnchors(FAnchors(0.f, 1.f));
        Slot->SetAlignment(FVector2D(0.f, 1.f));
        Slot->SetPosition(FVector2D(32.f, -28.f));
        Slot->SetAutoSize(true);
    }
}

void UDemoHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    RefreshText();
}

void UDemoHUDWidget::RefreshText()
{
    if (!StatusText) return;

    const ADemoGameMode* GM = Cast<ADemoGameMode>(UGameplayStatics::GetGameMode(this));
    const ADemoPlayerCharacter* Player = Cast<ADemoPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    int32 Wave = 0;
    int32 Alive = 0;
    for (TActorIterator<AWaveManager> It(GetWorld()); It; ++It)
    {
        if (IsValid(*It))
        {
            Wave = It->GetCurrentWave();
            Alive = It->GetAliveEnemyCount();
            break;
        }
    }

    const FString Text = FString::Printf(
        TEXT("HEALTH %.0f | WAVE %d | ENEMIES %d | SCORE %d"),
        Player ? Player->GetHealth() : 0.f,
        Wave,
        Alive,
        GM ? GM->GetScore() : 0);

    StatusText->SetText(FText::FromString(Text));
}
