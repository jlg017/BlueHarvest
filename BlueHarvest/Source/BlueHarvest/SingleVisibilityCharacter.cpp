// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleVisibilityCharacter.h"

#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"

#include "ActorComponents/SelectiveVisibilityComponent.h"
#include "AI/Controllers/FollowerAIController.h"

// Sets default values
ASingleVisibilityCharacter::ASingleVisibilityCharacter() : AAIEnemyCharacter()
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