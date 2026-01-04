// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacter.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AAIEnemyCharacter::AAIEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAIEnemyCharacter::Attack(APawn* Target)
{
	// TODO: play animation

	AActor* HitActor = DrawSphereTraceAndReturnHitCharacter();

	if (HitActor) {
		UE_LOG(LogTemp, Warning, TEXT("hit actor %s"), *HitActor->GetName());
		return true;
	}

	return false;
}

AActor* AAIEnemyCharacter::DrawSphereTraceAndReturnHitCharacter() {
	FVector StartLocation = GetActorLocation(); // Or any other starting point
	FVector EndLocation = StartLocation + GetActorForwardVector() * 1000.f; // 1000 units forward
	float TraceRadius = 50.f;
	FHitResult OutHit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	// Example: Add a specific object type, converting from ECollisionChannel to EObjectTypeQuery
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	UE_LOG(LogTemp, Warning, TEXT("Attacking"));

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		StartLocation,
		EndLocation, // TODO: Add some exta reach
		TraceRadius, // TODO: Make variable
		ObjectTypesArray,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		OutHit,
		true,
		FLinearColor::Green,
		FLinearColor::Red,
		10.f
	)) {
		UE_LOG(LogTemp, Warning, TEXT("HIT"));
		return OutHit.GetActor();
	}
	return nullptr;
}
