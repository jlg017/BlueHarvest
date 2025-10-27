// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectiveVisibilityComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
USelectiveVisibilityComponent::USelectiveVisibilityComponent()
{
	SetIsReplicatedByDefault(true);
}

void USelectiveVisibilityComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USelectiveVisibilityComponent, VisibleToPlayerId);
}

void USelectiveVisibilityComponent::SetVisibleToPlayerId(int32 NewVisibleToPlayerId) {
	if (GetOwner()->HasAuthority()) {
		VisibleToPlayerId = NewVisibleToPlayerId;
		OnRep_VisibleToPlayerId();
	}
}

void USelectiveVisibilityComponent::OnRep_VisibleToPlayerId()
{
	UpdateVisibility();
}

void USelectiveVisibilityComponent::UpdateVisibility()
{
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	if (Controller == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to update visibility; Controller is null"));
		return;
	}

	APlayerState* PlayerState = Controller->GetPlayerState<APlayerState>();
	if (PlayerState == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to update visibility; Player State is null"));
		return;
	}

	int32 PlayerId = PlayerState->GetPlayerId();
	UE_LOG(LogTemp, Warning, TEXT("Updating visibility for new TargetedPlayerId=%d; Local player id=%d"), VisibleToPlayerId, PlayerId);

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to update visibility; Character is null"));
		return;
	}

	if (VisibleToPlayerId == PlayerId) {
		Character->GetMesh()->SetVisibility(true);
	}
	else {
		Character->GetMesh()->SetVisibility(false);
	}
}