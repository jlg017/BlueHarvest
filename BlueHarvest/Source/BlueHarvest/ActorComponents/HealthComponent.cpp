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
	OnHealthChanged.Broadcast();

	if (Health == 0)
	{
		OnHealthDepleted.Broadcast();
	}
}

void UHealthComponent::UpdateHealth(float DeltaHealth)
{
	if (GetOwner()->HasAuthority()) {
		Server_UpdateHealth_Implementation(DeltaHealth);
	}
	else
	{
		Server_UpdateHealth(DeltaHealth);
	}
}

void UHealthComponent::Server_UpdateHealth_Implementation(float DeltaHealth)
{
	float PrevHealth = Health;
	float NewHealth = Health + DeltaHealth;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast();

	if (Health == 0)
	{
		OnHealthDepleted.Broadcast();
	}
}