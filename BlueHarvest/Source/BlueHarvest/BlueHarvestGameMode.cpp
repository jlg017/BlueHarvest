// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlueHarvestGameMode.h"
#include "BlueHarvestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlueHarvestGameMode::ABlueHarvestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
