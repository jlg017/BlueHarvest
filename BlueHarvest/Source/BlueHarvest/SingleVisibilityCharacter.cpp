// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleVisibilityCharacter.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

#include "BlueHarvest/GameStates/FollowerGameState.h"

// Sets default values
ASingleVisibilityCharacter::ASingleVisibilityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void ASingleVisibilityCharacter::BeginPlay()
{
	Super::BeginPlay();

	AFollowerGameState* MyGameState = Cast<AFollowerGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (MyGameState)
	{
		MyGameState->OnTargetedPlayerIdChanged.AddDynamic(this, &ASingleVisibilityCharacter::UpdateVisibility);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SingleVisibilityCharacter::GameState is null"));
	}
}

// Called to bind functionality to input
void ASingleVisibilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASingleVisibilityCharacter::UpdateVisibility(int32 TargetedPlayerId)
{
	int32 PlayerId = GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>()->GetPlayerId();

	UE_LOG(LogTemp, Display, TEXT("Updating visibility for new TargetedPlayerId=%d; Local player id=%d"), PlayerId, TargetedPlayerId);

	if (TargetedPlayerId == PlayerId) {
		GetMesh()->SetVisibility(true);
	}
	else {
		GetMesh()->SetVisibility(false);
	}
}