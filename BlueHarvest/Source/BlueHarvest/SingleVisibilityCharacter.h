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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 VisibleToPlayerIndex;
	float VisibilityChangeTimer;
	TArray<int32> PlayerIds;
	
	UFUNCTION(Client, Reliable)
	void UpdateVisibilityRPC();

	void GetPlayerIds();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
	float MaxVisibilityChangeTime = 5.f;

};
