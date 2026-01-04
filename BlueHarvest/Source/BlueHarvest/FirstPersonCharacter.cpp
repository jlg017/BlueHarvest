// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "ActorComponents/HealthComponent.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FirstPersonMesh != nullptr);

	// Only the owning player sees this mesh.
	FirstPersonMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FirstPersonMesh->SetupAttachment(FPCameraComponent);

	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

	// Set collision so mesh doesn't fall through floor on death
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	bReplicates = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	SetCanBeDamaged(true);

}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	if (HealthComponent)
	{
		FString HasAuthVal = HasAuthority() ? TEXT("true") : TEXT("false");
		UE_LOG(LogTemp, Warning, TEXT("Adding OnHealthDepleted delegate - HasAuthority=%s"), *HasAuthVal);
		HealthComponent->OnHealthDepleted.AddDynamic(this, &AFirstPersonCharacter::HandleDeath);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthComponent is NULL"));
	}
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//float AFirstPersonCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
//	UE_LOG(LogTemp, Warning, TEXT("Taking Damage: Damage = %f"), Damage);
//	if(HasAuthority())
//	{
//		HealthComponent->UpdateHealth(-Damage);
//	}
//	
//	return Damage;
//}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	// TODO: Update to use Enhanced Input
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFirstPersonCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirstPersonCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::JumpButtonPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFirstPersonCharacter::JumpButtonReleased);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFirstPersonCharacter::CrouchButtonPressed);
}

void AFirstPersonCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFirstPersonCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFirstPersonCharacter::JumpButtonPressed()
{
	bPressedJump = true;
}

void AFirstPersonCharacter::JumpButtonReleased()
{
	bPressedJump = false;
}

void AFirstPersonCharacter::CrouchButtonPressed()
{
	if (bIsCrouched) {
		UnCrouch();
	}
	else {
		Crouch();
	}
}

void AFirstPersonCharacter::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player %s died"), *GetName());
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {
		DisableInput(PlayerController);
		FirstPersonMesh->SetVisibility(false);
	}
	GetMesh()->SetSimulatePhysics(true);
}