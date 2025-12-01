// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLUEHARVEST_API AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/*
	* TODO Add additional functionality to set up HUD and controller
	*/
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	class AGameHUD* GameHUD;
};
