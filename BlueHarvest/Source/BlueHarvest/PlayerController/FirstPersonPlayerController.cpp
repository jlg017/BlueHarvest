// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayerController.h"
#include "BlueHarvest/FirstPersonCharacter.h"
#include "BlueHarvest/ActorComponents/HealthComponent.h"
#include "BlueHarvest/UI/HUD/GameHUD.h"

void AFirstPersonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameHUD = Cast<AGameHUD>(GetHUD());
	
}