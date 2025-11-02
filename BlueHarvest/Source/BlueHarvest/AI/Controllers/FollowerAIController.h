// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Net/UnrealNetwork.h"
#include "FollowerAIController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetPlayerIdChanged, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisibleToPlayerIdChanged, int32, NewValue);
/**
 * 
 */
UCLASS()
class BLUEHARVEST_API AFollowerAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE int32 GetTargetPlayerId() { return TargetPlayerId; }
	FORCEINLINE int32 GetVisibleToPlayerId() { return VisibleToPlayerId; }

	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnTargetPlayerIdChanged OnTargetPlayerIdChanged;

	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnVisibleToPlayerIdChanged OnVisibleToPlayerIdChanged;

protected:

	// used for default player targeting behaviour
	UPROPERTY(EditAnywhere)
	float MaxTargetedTime = 5.0f;
	UPROPERTY(EditAnywhere)
	float CurrentTargetedTime = 0.0f;

	/*
	* Target Player Id
	*/
	UFUNCTION(BlueprintCallable)
	void SetTargetPlayerId(int32 NewTargetPlayerId);

	UFUNCTION(BlueprintNativeEvent)
	bool ShouldUpdateTargetPlayerId(float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateTargetPlayerId();

	/*
	* Visible To Player Id
	*/
	UFUNCTION(BlueprintCallable)
	void SetVisibleToPlayerId(int32 NewVisibleToPlayerId);

	UFUNCTION(BlueprintNativeEvent)
	bool ShouldUpdateVisibleToPlayerId(float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateVisibleToPlayerId();

private:

	int32 TargetPlayerId;
	int32 VisibleToPlayerId;

};
