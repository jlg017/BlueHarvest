// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SingleVisibilityCharacter.generated.h"

UCLASS()
class BLUEHARVEST_API ASingleVisibilityCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASingleVisibilityCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USelectiveVisibilityComponent* VisibilityComponent;

private:
	int32 VisibleToPlayerId;
	
	UFUNCTION()
	virtual void UpdateVisibleToPlayerId(int32 TargetedPlayerId);

};
