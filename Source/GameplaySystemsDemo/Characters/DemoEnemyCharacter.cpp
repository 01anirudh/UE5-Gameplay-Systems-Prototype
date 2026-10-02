#include "Characters/DemoEnemyCharacter.h"
#include "Characters/DemoPlayerCharacter.h"
#include "Game/DemoGameMode.h"
#include "AI/DemoAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ADemoEnemyCharacter::ADemoEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    AIControllerClass = ADemoAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    UStaticMeshComponent* Visual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
    Visual->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (Sphere.Succeeded())
    {
        Visual->SetStaticMesh(Sphere.Object);
        Visual->SetRelativeScale3D(FVector(0.65f));
    }
}

void ADemoEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    GetWorldTimerManager().SetTimer(ContactDamageTimerHandle, this, &ADemoEnemyCharacter::TryDamagePlayer, 0.5f, true);
}

float ADemoEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const&, AController*, AActor*)
{
    const float AppliedDamage = FMath::Clamp(DamageAmount, 0.f, Health);
    Health -= AppliedDamage;
    if (Health <= 0.f)
    {
        Die();
    }
    return AppliedDamage;
}

void ADemoEnemyCharacter::TryDamagePlayer()
{
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (Player && FVector::DistSquared(GetActorLocation(), Player->GetActorLocation()) <= FMath::Square(ContactDistance))
    {
        UGameplayStatics::ApplyDamage(Player, ContactDamage, GetController(), this, UDamageType::StaticClass());
    }
}

void ADemoEnemyCharacter::Die()
{
    if (ADemoGameMode* GM = Cast<ADemoGameMode>(UGameplayStatics::GetGameMode(this)))
    {
        GM->NotifyEnemyDefeated();
    }
    Destroy();
}
