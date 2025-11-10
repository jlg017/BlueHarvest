// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"


void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}

UHealthComponent::UHealthComponent()
{
	SetIsReplicatedByDefault(true);
	Health = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::OnRep_Health(float PreviousHealth)
{
	// send notify for local animation play, etc. 
}

void UHealthComponent::UpdateHealth(float DeltaHealth)
{
	float NewHealth = Health + DeltaHealth;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	if (Health == 0)
	{
		OnHealthDepleted.Broadcast();
	}
}