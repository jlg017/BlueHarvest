// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowerGameMode.h"
#include "BlueHarvest/GameStates/FollowerGameState.h"

#include "GameFramework/PlayerState.h"


AFollowerGameMode::AFollowerGameMode()
{
	GameStateClass = AFollowerGameState::StaticClass();
}

void AFollowerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ShouldUpdateTargetPlayerId(DeltaSeconds))
	{
		UpdateTargetPlayerId();
	}
}

void AFollowerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	if (GameStateClass == nullptr) {
		GameStateClass = AFollowerGameState::StaticClass();
	}
	
	Super::InitGame(MapName, Options, ErrorMessage);
	
	UpdateTargetPlayerId();

	/*
	if (GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Initing targeted player"));
		TArray<TObjectPtr<APlayerState>> Players = GameState->PlayerArray;
		for (TObjectPtr<APlayerState> Player : Players)
		{
			if (Player.Get() != nullptr)
			{
				APlayerState* PlayerState = Player.Get();
				UE_LOG(LogTemp, Warning, TEXT("Initing target to playerid=%d"), PlayerState->GetPlayerId());
				SetTargetedPlayerId(PlayerState->GetPlayerId());
				return;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Player is null"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState is null"));
	}
	*/
}

bool AFollowerGameMode::ShouldUpdateTargetPlayerId(float DeltaSeconds)
{
	CurrentTargetedTime += DeltaSeconds;
	if (CurrentTargetedTime > MaxTargetedTime)
	{
		CurrentTargetedTime = 0.0f;
		return true;
	}
	return false;
}

void AFollowerGameMode::UpdateTargetPlayerId()
{
	if (GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Updating targeted player"));
		UE_LOG(LogTemp, Warning, TEXT("Current targeted player=%d"), TargetedPlayerId);

		TArray<TObjectPtr<APlayerState>> Players = GameState->PlayerArray;
		for (TObjectPtr<APlayerState> Player : Players)
		{
			if (Player.Get() != nullptr)
			{
				APlayerState* PlayerState = Player.Get();
				UE_LOG(LogTemp, Display, TEXT("Checking playerid=%d for retargeting"), PlayerState->GetPlayerId());
				if (PlayerState->GetPlayerId() != TargetedPlayerId)
				{
					UE_LOG(LogTemp, Display, TEXT("Retargeting to playerid=%d"), PlayerState->GetPlayerId());
					SetTargetedPlayerId(PlayerState->GetPlayerId());
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

void AFollowerGameMode::SetTargetedPlayerId(int32 NewTargetedPlayerId)
{
	if (TargetedPlayerId == NewTargetedPlayerId)
	{
		return;
	}

	UE_LOG(LogGameMode, Display, TEXT("Targeted player Changed from %d to %d"), TargetedPlayerId, NewTargetedPlayerId);
	TargetedPlayerId = NewTargetedPlayerId;

	//OnTargetedPlayerChanged();

	AFollowerGameState* FullGameState = GetGameState<AFollowerGameState>();
	if (FullGameState)
	{
		FullGameState->SetTargetedPlayerId(NewTargetedPlayerId);
	}
}