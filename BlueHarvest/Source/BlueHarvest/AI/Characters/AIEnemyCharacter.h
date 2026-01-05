// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemyCharacter.generated.h"

UCLASS()
class BLUEHARVEST_API AAIEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool Attack(APawn* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Attack parameters
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackRange = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackDamage = 50.0f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackCooldownTime = 5.f;

private:

	// Attack cooldown logic
	// TODO: Replace with Timer implementation
	bool bCanAttack = true;
	float AttackCooldown = 0.f;

	void PerformAttackTrace();
};
