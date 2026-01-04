// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleVisibilityCharacter.h"

#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ActorComponents/SelectiveVisibilityComponent.h"
#include "AI/Controllers/FollowerAIController.h"

// Sets default values
ASingleVisibilityCharacter::ASingleVisibilityCharacter()
{
	bReplicates = true;

	VisibilityComponent = CreateDefaultSubobject<USelectiveVisibilityComponent>(TEXT("SelectiveVisibilityComponent"));
	AIControllerClass = AFollowerAIController::StaticClass();

	GetCharacterMovement()->bOrientRotationToMovement = false; //

	// Enable using controller rotation for specific axes
	bUseControllerRotationPitch = false; // Set to true if you need pitch rotation
	bUseControllerRotationYaw = false;   // Set to true if you need yaw rotation
	bUseControllerRotationRoll = false;  // Set to true if you need roll rotation

	// For smooth rotation with AI focus (which uses the controller rotation internally), 
	// you might also want to set this in the movement component:
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	// You can also adjust rotation rates:
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

// Called when the game starts or when spawned
void ASingleVisibilityCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		AFollowerAIController* AIController = GetController<AFollowerAIController>();
		if (AIController)
		{
			AIController->OnVisibleToPlayerIdChanged.AddDynamic(this, &ASingleVisibilityCharacter::UpdateVisibleToPlayerId);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BeginPlay - VisibilityComponent is null"));
		}
	}
}

void ASingleVisibilityCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bCanAttack)
    {
        AttackCooldown -= DeltaTime;
        if (AttackCooldown <= 0.f)
        {
            AttackCooldown = 0.f;
            bCanAttack = true;
        }
    }
}

// Called to bind functionality to input
void ASingleVisibilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASingleVisibilityCharacter::UpdateVisibleToPlayerId(int32 NewVisibleToPlayerId)
{
	if (GetOwner()->HasAuthority()) {
		UE_LOG(LogTemp, Warning, TEXT("OnVisibleToPlayerIdChanged delegate fired on server"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("OnVisibleToPlayerIdChanged delegate fired NOT on server"));
	}
	VisibleToPlayerId = NewVisibleToPlayerId;
	VisibilityComponent->SetVisibleToPlayerId(NewVisibleToPlayerId);
}

bool ASingleVisibilityCharacter::Attack(APawn* Target) 
{
	ACharacter* TargetCharacter = Cast<ACharacter>(Target);
	if (TargetCharacter && bCanAttack) {
        if (HasAuthority()) {
            // Deal damage on server
            AttackCooldown = AttackCooldownTime;
            bCanAttack = false;
            UE_LOG(LogTemp, Warning, TEXT("Attacking player '%s'"), *TargetCharacter->GetName());
            PerformAttackTrace();
        }
        // TODO: Play animations, etc. on server and clients
        return true;
	}

	return false;
}

void ASingleVisibilityCharacter::PerformAttackTrace()
{
    // Define start and end points (can be the same for a single-location sphere trace)
    // A common approach is to use a socket on a weapon or hand bone
    FVector StartLocation = GetActorLocation(); //GetMesh()->GetSocketLocation(FName("AttackStartSocket"));
    FVector EndLocation = GetActorLocation() + (GetActorForwardVector() * AttackRange); //GetMesh()->GetSocketLocation(FName("AttackEndSocket"));
    float TraceRadius = 50.0f; // Adjust as needed (Unreal units are in centimeters)

    // Array to store hit results
    TArray<FHitResult> HitResults;

    // Array of actors to ignore (e.g., the character performing the attack)
    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    // Collision channel to trace against (e.g., ECC_Pawn or a custom trace channel)
    ECollisionChannel TraceChannel = ECC_Pawn;

    // Perform the sphere trace
    bool bHit = UKismetSystemLibrary::SphereTraceMulti(
        GetWorld(),
        StartLocation,
        EndLocation,
        TraceRadius,
        UEngineTypes::ConvertToTraceType(TraceChannel),
        false, // bTraceComplex
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration, // Draw debug sphere for visualization
        HitResults,
        true, // bIgnoreSelf
        FLinearColor::Red,
        FLinearColor::Green,
        1.0f // Draw time
    );

    // Process hits
    if (bHit)
    {
        // Used to ensure we only apply damage once to each actor as multiple hits can register
        // TODO: See if we can refactor to use a single trace channel to eliminate multi-hits
        TArray<AActor*> SeenActors = TArray<AActor*>();
        for (const FHitResult& Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && !SeenActors.Contains(HitActor))
            {
                SeenActors.Add(HitActor);

                // Apply damage
                float Damage = UGameplayStatics::ApplyDamage(
                    HitActor, 
                    AttackDamage,
                    GetController(), 
                    this, 
                    UDamageType::StaticClass()
                );
                UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s for %f damage"), *HitActor->GetName(), Damage);
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("Hit Actor is NULL or has already been hit"));
            }
        }
    }
}