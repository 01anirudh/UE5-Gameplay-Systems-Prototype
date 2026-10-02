#include "Characters/DemoPlayerCharacter.h"
#include "Characters/DemoEnemyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

ADemoPlayerCharacter::ADemoPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    bUseControllerRotationYaw = false;
    GetMesh()->SetVisibility(false);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 900.f;
    CameraBoom->SetRelativeRotation(FRotator(-58.f, 0.f, 0.f));

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

    MappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("MappingContext"));
    ForwardAction = CreateDefaultSubobject<UInputAction>(TEXT("ForwardAction"));
    BackAction = CreateDefaultSubobject<UInputAction>(TEXT("BackAction"));
    RightAction = CreateDefaultSubobject<UInputAction>(TEXT("RightAction"));
    LeftAction = CreateDefaultSubobject<UInputAction>(TEXT("LeftAction"));
    FireAction = CreateDefaultSubobject<UInputAction>(TEXT("FireAction"));

    ForwardAction->ValueType = EInputActionValueType::Boolean;
    BackAction->ValueType = EInputActionValueType::Boolean;
    RightAction->ValueType = EInputActionValueType::Boolean;
    LeftAction->ValueType = EInputActionValueType::Boolean;
    FireAction->ValueType = EInputActionValueType::Boolean;

    MappingContext->MapKey(ForwardAction, EKeys::W);
    MappingContext->MapKey(BackAction, EKeys::S);
    MappingContext->MapKey(RightAction, EKeys::D);
    MappingContext->MapKey(LeftAction, EKeys::A);
    MappingContext->MapKey(FireAction, EKeys::SpaceBar);
}

void ADemoPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                Subsystem->AddMappingContext(MappingContext, 0);
            }
        }
    }
}

void ADemoPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EI->BindAction(ForwardAction, ETriggerEvent::Triggered, this, [this](const FInputActionValue& V){ MoveForward(V, 1.f); });
        EI->BindAction(BackAction, ETriggerEvent::Triggered, this, [this](const FInputActionValue& V){ MoveForward(V, -1.f); });
        EI->BindAction(RightAction, ETriggerEvent::Triggered, this, [this](const FInputActionValue& V){ MoveRight(V, 1.f); });
        EI->BindAction(LeftAction, ETriggerEvent::Triggered, this, [this](const FInputActionValue& V){ MoveRight(V, -1.f); });
        EI->BindAction(FireAction, ETriggerEvent::Started, this, &ADemoPlayerCharacter::Fire);
    }
}

void ADemoPlayerCharacter::MoveForward(const FInputActionValue& Value, float Scale)
{
    if (!Value.Get<bool>() || !Controller) return;
    const FRotator R(0.f, Controller->GetControlRotation().Yaw, 0.f);
    AddMovementInput(FRotationMatrix(R).GetUnitAxis(EAxis::X), Scale);
}

void ADemoPlayerCharacter::MoveRight(const FInputActionValue& Value, float Scale)
{
    if (!Value.Get<bool>() || !Controller) return;
    const FRotator R(0.f, Controller->GetControlRotation().Yaw, 0.f);
    AddMovementInput(FRotationMatrix(R).GetUnitAxis(EAxis::Y), Scale);
}

void ADemoPlayerCharacter::Fire()
{
    if (bFireOnCooldown) return;
    bFireOnCooldown = true;

    FTimerHandle Cooldown;
    GetWorldTimerManager().SetTimer(Cooldown, [this](){ bFireOnCooldown = false; }, FireCooldown, false);

    if (AActor* Target = FindNearestEnemy())
    {
        UGameplayStatics::ApplyDamage(Target, FireDamage, GetController(), this, UDamageType::StaticClass());
    }
}

float ADemoPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const&, AController*, AActor*)
{
    Health -= FMath::Clamp(DamageAmount, 0.f, Health);
    if (Health <= 0.f)
    {
        Health = MaxHealth;
        SetActorLocation(FVector::ZeroVector);
    }
    return DamageAmount;
}

AActor* ADemoPlayerCharacter::FindNearestEnemy() const
{
    AActor* Best = nullptr;
    float BestDistanceSq = FMath::Square(AutoAimRadius);

    for (TActorIterator<ADemoEnemyCharacter> It(GetWorld()); It; ++It)
    {
        if (!IsValid(*It)) continue;
        const float D2 = FVector::DistSquared(GetActorLocation(), It->GetActorLocation());
        if (D2 < BestDistanceSq)
        {
            BestDistanceSq = D2;
            Best = *It;
        }
    }
    return Best;
}
