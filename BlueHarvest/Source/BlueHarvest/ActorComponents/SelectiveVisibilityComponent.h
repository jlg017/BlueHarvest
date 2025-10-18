// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectiveVisibilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEHARVEST_API USelectiveVisibilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Sets default values for this component's properties
	USelectiveVisibilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY(ReplicatedUsing = OnRep_TargetedPlayerId, BlueprintReadOnly, Category = Target)
	int32 TargetedPlayerId;

	virtual bool ShouldUpdateTargetPlayerId(float DeltaSeconds);

	UFUNCTION(Server, Reliable)
	virtual void Server_UpdateTargetPlayerId();

private:

	float MaxTargetedTime = 5.0f;
	float CurrentTargetedTime = 0.0f;
		
	UFUNCTION()
	virtual void OnRep_TargetedPlayerId();
};
