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

	bool Attack(APawn* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Attack parameters
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USelectiveVisibilityComponent* VisibilityComponent;

private:
	int32 VisibleToPlayerId;
	
	// Attack cooldown logic
	// TODO: Replace with Timer implementation
	bool bCanAttack = true;
	float AttackCooldown = 0.f;
	float AttackCooldownTime = 5.f;

	UFUNCTION()
	virtual void UpdateVisibleToPlayerId(int32 TargetedPlayerId);

	void PerformAttackTrace();
};
