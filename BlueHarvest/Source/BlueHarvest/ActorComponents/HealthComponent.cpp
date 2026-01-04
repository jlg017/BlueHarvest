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
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		// Bind the damage handling function to the Actor's built-in damage event
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Owner is null"));
	}
}

void UHealthComponent::OnRep_Health(float PreviousHealth)
{
	OnHealthChanged.Broadcast();

	if (Health <= 0.0f)
	{
		OnHealthDepleted.Broadcast();
	}
}

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Player '%s' has taken %f damage"), *GetName(), Damage);
	UpdateHealth(-Damage);
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

	if (Health <= 0.0f)
	{
		OnHealthDepleted.Broadcast();
	}
}