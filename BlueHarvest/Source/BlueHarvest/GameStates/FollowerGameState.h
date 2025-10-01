// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FollowerGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetedPlayerIdChanged, int32, NewValue);

/**
 * 
 */
UCLASS()
class BLUEHARVEST_API AFollowerGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int32 GetTargetedPlayerId() const { return TargetedPlayerId; }

	/** Updates the targeted player id and calls the appropriate transition functions, only valid on server */
	void SetTargetedPlayerId(int32 NewTargetPlayerId);

	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnTargetedPlayerIdChanged OnTargetedPlayerIdChanged;
	
protected:

	/** Which player is currently target */
	UPROPERTY(ReplicatedUsing = OnRep_TargetedPlayerId, BlueprintReadOnly, VisibleInstanceOnly, Category = GameState)
	int32 TargetedPlayerId;

	/** Previous targeted player id, used to handle if multiple transitions happen per frame */
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = GameState)
	int32 PreviousTargetedPlayerId;

public:

	/** Targeted player id has changed */
	UFUNCTION()
	virtual void OnRep_TargetedPlayerId();
};
