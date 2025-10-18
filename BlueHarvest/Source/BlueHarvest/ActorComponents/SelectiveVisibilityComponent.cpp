// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectiveVisibilityComponent.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Character.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
USelectiveVisibilityComponent::USelectiveVisibilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	// ...
}

void USelectiveVisibilityComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USelectiveVisibilityComponent, TargetedPlayerId);
}


// Called when the game starts
void USelectiveVisibilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority()) {
		CurrentTargetedTime = 0;
		Server_UpdateTargetPlayerId();
	}
}


// Called every frame
void USelectiveVisibilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->HasAuthority() && ShouldUpdateTargetPlayerId(DeltaTime)) {
		Server_UpdateTargetPlayerId();
	}
}

bool USelectiveVisibilityComponent::ShouldUpdateTargetPlayerId(float DeltaSeconds)
{
	CurrentTargetedTime += DeltaSeconds;
	if (CurrentTargetedTime > MaxTargetedTime)
	{
		CurrentTargetedTime = 0.0f;
		return true;
	}
	return false;
}

void USelectiveVisibilityComponent::Server_UpdateTargetPlayerId_Implementation()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Updating targeted player"));
		UE_LOG(LogTemp, Warning, TEXT("Current targeted player=%d"), TargetedPlayerId);

		TArray<TObjectPtr<APlayerState>> Players = GameState->PlayerArray;

		for (int i = 0; i <= Players.Num(); i++) {
			int32 index = FMath::RandRange(0, Players.Num() - 1);
			TObjectPtr<APlayerState> Player = Players[index];

			if (Player.Get() != nullptr)
			{
				APlayerState* PlayerState = Player.Get();
				UE_LOG(LogTemp, Display, TEXT("Checking playerid=%d for retargeting"), PlayerState->GetPlayerId());
				if (PlayerState->GetPlayerId() != TargetedPlayerId)
				{
					UE_LOG(LogTemp, Display, TEXT("Retargeting to playerid=%d"), PlayerState->GetPlayerId());
					TargetedPlayerId = PlayerState->GetPlayerId();
					OnRep_TargetedPlayerId();
					return;
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Player is null. Not updating targeted player"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode::GameState is null"));
	}
}

void USelectiveVisibilityComponent::OnRep_TargetedPlayerId()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to update visibility; Controller is null"));
		return;
	}

	APlayerState* PlayerState = Controller->GetPlayerState<APlayerState>();
	if (PlayerState == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to update visibility; Player State is null"));
		return;
	}

	int32 PlayerId = PlayerState->GetPlayerId();
	UE_LOG(LogTemp, Warning, TEXT("Updating visibility for new TargetedPlayerId=%d; Local player id=%d"), PlayerId, TargetedPlayerId);

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to update visibility; Character is null"));
		return;
	}

	if (TargetedPlayerId == PlayerId) {
		Character->GetMesh()->SetVisibility(true);
	}
	else {
		Character->GetMesh()->SetVisibility(false);
	}
}