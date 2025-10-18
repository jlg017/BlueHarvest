// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleVisibilityCharacter.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

#include "GameStates/FollowerGameState.h"
#include "ActorComponents/SelectiveVisibilityComponent.h"

// Sets default values
ASingleVisibilityCharacter::ASingleVisibilityCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	VisibilityComponent = CreateDefaultSubobject<USelectiveVisibilityComponent>(TEXT("SelectiveVisibilityComponent"));
}

// Called when the game starts or when spawned
void ASingleVisibilityCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ASingleVisibilityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}