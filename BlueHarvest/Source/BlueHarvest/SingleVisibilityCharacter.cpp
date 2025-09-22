// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleVisibilityCharacter.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"

// Sets default values
ASingleVisibilityCharacter::ASingleVisibilityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	PlayerIds = TArray<int32>();
}

// Called when the game starts or when spawned
void ASingleVisibilityCharacter::BeginPlay()
{
	Super::BeginPlay();

	VisibleToPlayerIndex = 0;
	VisibilityChangeTimer = 0.f;
}

// Called every frame
void ASingleVisibilityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	VisibilityChangeTimer += DeltaTime;
	//UE_LOG(LogTemp, Warning, TEXT("Tick;VisibilityChangeTimer=%f;MaxVisibilityChangeTime=%f"), VisibilityChangeTimer, MaxVisibilityChangeTime);
	if (VisibilityChangeTimer > MaxVisibilityChangeTime)
	{
		VisibleToPlayerIndex = VisibleToPlayerIndex == 0 ? 1 : 0;
		VisibilityChangeTimer = 0;

		if (PlayerIds.Num() == 0) {
			GetPlayerIds();
		}

		UpdateVisibilityRPC();
	}

}

// Called to bind functionality to input
void ASingleVisibilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASingleVisibilityCharacter::GetPlayerIds() {
	PlayerIds = TArray<int32>();
	AGameStateBase* GameState = GetWorld()->GetGameState<AGameStateBase>();
	if (GameState) {
		TArray<APlayerState*> Players = GameState->PlayerArray;
		if (Players.Num() == 0) {
			UE_LOG(LogTemp, Warning, TEXT("No Player states found"));
			return;
		}
		for (APlayerState* Player : Players) {
			int32 PlayerId = Player->PlayerId;
			PlayerIds.Add(PlayerId);
			UE_LOG(LogTemp, Warning, TEXT("Adding ID=%d"), PlayerId);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Game state is null"));
	}
}

void ASingleVisibilityCharacter::UpdateVisibilityRPC_Implementation() {
	if (PlayerIds.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No player ids to search, making invisible"));
		GetMesh()->SetVisibility(false);
		return;
	}

	//TODO: Change visibility
	int32 PlayerId = GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>()->PlayerId;
	int32 VisiblePlayerId = PlayerIds[VisibleToPlayerIndex];
	UE_LOG(LogTemp, Warning, TEXT("LocalNetId=%d; VisiblePlayerNetId=%d"), PlayerId, VisiblePlayerId);
	if (VisiblePlayerId == PlayerId) {
		GetMesh()->SetVisibility(true);
	}
	else {
		GetMesh()->SetVisibility(false);
	}
}
