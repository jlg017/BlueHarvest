// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleVisibilityCharacter.h"

#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"

#include "ActorComponents/SelectiveVisibilityComponent.h"
#include "AI/Controllers/FollowerAIController.h"

// Sets default values
ASingleVisibilityCharacter::ASingleVisibilityCharacter()
{
	bReplicates = true;

	VisibilityComponent = CreateDefaultSubobject<USelectiveVisibilityComponent>(TEXT("SelectiveVisibilityComponent"));
	AIControllerClass = AFollowerAIController::StaticClass();
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
	return Super::Attack(Target);
}