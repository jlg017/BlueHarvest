// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEHARVEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

protected:

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = Health)
	float Health;
	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxHealth;

	virtual void BeginPlay() override;
	// Applies Heal or Damage amount to Health
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float DeltaHealth);

private:

	UFUNCTION()
	virtual void OnRep_Health(float DeltaHealth);

		
};
