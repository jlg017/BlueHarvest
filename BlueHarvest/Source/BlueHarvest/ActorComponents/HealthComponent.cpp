// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"


UHealthComponent::UHealthComponent()
{
	SetIsReplicatedByDefault(true);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}

void UHealthComponent::OnRep_Health(float DeltaHealth)
{
	UpdateHealth(DeltaHealth);
}

void UHealthComponent::UpdateHealth(float DeltaHealth)
{
	float NewHealth = Health + DeltaHealth;
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}