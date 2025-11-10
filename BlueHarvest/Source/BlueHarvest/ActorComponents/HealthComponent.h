// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEHARVEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UHealthComponent();

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float DeltaHealth);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthDepleted OnHealthDepleted;

protected:

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = Health)
	float Health = 0;
	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxHealth = 100;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	virtual void OnRep_Health(float PreviousHealth);

};
