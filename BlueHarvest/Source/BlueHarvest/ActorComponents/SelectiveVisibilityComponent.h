// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectiveVisibilityComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLUEHARVEST_API USelectiveVisibilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Sets default values for this component's properties
	USelectiveVisibilityComponent();

	void SetVisibleToPlayerId(int32 NewVisibleToPlayerId);
	FORCEINLINE int32 GetVisibleToPlayerId() { return VisibleToPlayerId; }

protected:

	UPROPERTY(ReplicatedUsing = OnRep_VisibleToPlayerId, BlueprintReadOnly, Category = Target)
	int32 VisibleToPlayerId;

private:
		
	UFUNCTION()
	virtual void OnRep_VisibleToPlayerId();

	void UpdateVisibility();
};
