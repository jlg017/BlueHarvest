// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEHARVEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float DeltaHealth);

	UFUNCTION(Server, Reliable)
	void Server_UpdateHealth(float DeltaHealth);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthDepleted OnHealthDepleted;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthDepleted OnHealthChanged;

protected:

	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = Health)
	float Health = 0;
	UPROPERTY(EditDefaultsOnly, Category = Health)
	float MaxHealth = 100;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnRep_Health(float PreviousHealth);

};
