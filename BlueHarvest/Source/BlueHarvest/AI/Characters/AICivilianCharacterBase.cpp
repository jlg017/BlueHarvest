// Fill out your copyright notice in the Description page of Project Settings.


#include "AICivilianCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICivilianCharacterBase::AAICivilianCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// bReplicates = true; Uncomment if replication needed

    GetCharacterMovement()->bOrientRotationToMovement = false; //

    // Enable using controller rotation for specific axes
    bUseControllerRotationPitch = false; // Set to true if you need pitch rotation
    bUseControllerRotationYaw = false;   // Set to true if you need yaw rotation
    bUseControllerRotationRoll = false;  // Set to true if you need roll rotation

    // For smooth rotation with AI focus (which uses the controller rotation internally), 
    // you might also want to set this in the movement component:
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    // You can also adjust rotation rates:
    //GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

// Called when the game starts or when spawned
void AAICivilianCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICivilianCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICivilianCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
