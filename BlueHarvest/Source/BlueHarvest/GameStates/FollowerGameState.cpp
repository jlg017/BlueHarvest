// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowerGameState.h"
#include "Net/UnrealNetwork.h"

void AFollowerGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFollowerGameState, TargetedPlayerId);
}

void AFollowerGameState::SetTargetedPlayerId(int32 NewTargetedPlayerId)
{
	if (HasAuthority())
	{
		UE_LOG(LogGameState, Log, TEXT("TargetedPlayerId Changed from %d to %d"), TargetedPlayerId, NewTargetedPlayerId);

		TargetedPlayerId = NewTargetedPlayerId;

		// Call the onrep to make sure the callbacks happen
		OnRep_TargetedPlayerId();
	}
}

void AFollowerGameState::OnRep_TargetedPlayerId()
{
	if (PreviousTargetedPlayerId != TargetedPlayerId)
	{
		//OnTargetedPlayerIdChanged.Broadcast(TargetedPlayerId);
	}
	PreviousTargetedPlayerId = TargetedPlayerId;
}