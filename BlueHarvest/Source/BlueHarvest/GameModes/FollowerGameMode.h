// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FollowerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLUEHARVEST_API AFollowerGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AFollowerGameMode();

	virtual void Tick(float DeltaSeconds) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/*
protected:

	UPROPERTY(Transient)
	int32 TargetedPlayerId;

	virtual bool ShouldUpdateTargetPlayerId(float DeltaSeconds);
	virtual void UpdateTargetPlayerId();
	virtual void SetTargetedPlayerId(int32 NewTargetedPlayerId);

private:

	float MaxTargetedTime = 5.0f;
	float CurrentTargetedTime = 0.0f;
	*/
};
