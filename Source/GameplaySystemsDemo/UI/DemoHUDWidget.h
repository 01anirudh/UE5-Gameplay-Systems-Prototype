#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoHUDWidget.generated.h"

class UCanvasPanel;
class UTextBlock;

UCLASS()
class GAMEPLAYSYSTEMSDEMO_API UDemoHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    void RefreshText();

    UPROPERTY()
    TObjectPtr<UCanvasPanel> RootCanvas;

    UPROPERTY()
    TObjectPtr<UTextBlock> StatusText;

    UPROPERTY()
    TObjectPtr<UTextBlock> ControlsText;
};
