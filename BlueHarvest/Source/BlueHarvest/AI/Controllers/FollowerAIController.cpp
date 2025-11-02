// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowerAIController.h"

#include "BlueHarvest/ActorComponents/SelectiveVisibilityComponent.h"
#include "BlueHarvest/SingleVisibilityCharacter.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"


void AFollowerAIController::Tick(float DeltaTime) 
{
	if (ShouldUpdateTargetPlayerId(DeltaTime)) {
		UpdateTargetPlayerId();
	}

	if (ShouldUpdateVisibleToPlayerId(DeltaTime)) {
		UpdateVisibleToPlayerId();
	}
}

void AFollowerAIController::SetTargetPlayerId(int32 NewTargetPlayerId)
{
	TargetPlayerId = NewTargetPlayerId;
	if (TargetPlayerId != NewTargetPlayerId) {
		TargetPlayerId = NewTargetPlayerId;
		OnTargetPlayerIdChanged.Broadcast(NewTargetPlayerId);
	}
}

bool AFollowerAIController::ShouldUpdateTargetPlayerId_Implementation(float DeltaSeconds)
{
	CurrentTargetedTime += DeltaSeconds;
	if (CurrentTargetedTime > MaxTargetedTime)
	{
		CurrentTargetedTime = 0.0f;
		return true;
	}
	return false;
}

void AFollowerAIController::UpdateTargetPlayerId_Implementation()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Updating targeted player"));
		UE_LOG(LogTemp, Warning, TEXT("Current targeted player=%d"), TargetPlayerId);

		TArray<TObjectPtr<APlayerState>> Players = GameState->PlayerArray;
		for (int i = 0; i <= Players.Num(); i++) {
			int32 index = FMath::RandRange(0, Players.Num() - 1);
			TObjectPtr<APlayerState> Player = Players[index];

			if (Player.Get() != nullptr)
			{
				APlayerState* TargetPlayerState = Player.Get();
				UE_LOG(LogTemp, Display, TEXT("Checking playerid=%d for retargeting"), TargetPlayerState->GetPlayerId());
				if (TargetPlayerState->GetPlayerId() != TargetPlayerId)
				{
					UE_LOG(LogTemp, Display, TEXT("Retargeting to playerid=%d"), TargetPlayerState->GetPlayerId());
					SetTargetPlayerId(TargetPlayerState->GetPlayerId());
					UpdateVisibleToPlayerId();

					APawn* TargetPlayer = TargetPlayerState->GetPawn();
					if (TargetPlayer) {
						TargetPlayerPawn = TargetPlayer;
						UE_LOG(LogTemp, Warning, TEXT("Moving to Actor %s"), *TargetPlayer->GetName());
						MoveToActor(TargetPlayerPawn, 5.0f, false);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Failed to moving to actor. Actor is null"));
					}
					break;
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

/*
* Visible To Player Id
*/
void AFollowerAIController::SetVisibleToPlayerId(int32 NewVisibleToPlayerId)
{
	if (VisibleToPlayerId != NewVisibleToPlayerId) {
		VisibleToPlayerId = NewVisibleToPlayerId;
		OnVisibleToPlayerIdChanged.Broadcast(NewVisibleToPlayerId);
	}
}

bool AFollowerAIController::ShouldUpdateVisibleToPlayerId_Implementation(float DeltaSeconds)
{
	return false;
}

UFUNCTION(BlueprintNativeEvent)
void AFollowerAIController::UpdateVisibleToPlayerId_Implementation()
{
	SetVisibleToPlayerId(TargetPlayerId);
}

void AFollowerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	// TODO: Attack?
	MoveToActor(TargetPlayerPawn, 5.0f, false);
}