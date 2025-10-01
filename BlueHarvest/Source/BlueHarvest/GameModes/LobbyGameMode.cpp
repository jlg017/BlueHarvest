// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "MultiplayerSessionsSubsystem.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin called"));
	Super::PostLogin(NewPlayer);

	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UMultiplayerSessionsSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
		check(Subsystem);

		FString* LobbyCode = Subsystem->DesiredMatchProperties.Find(FName("LobbyCode"));
		if (LobbyCode) {
			UE_LOG(LogTemp, Warning, TEXT("LobbyCode=%s"), **LobbyCode);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No lobby code"));
		}

		UE_LOG(LogTemp, Display, TEXT("NumberOfPlayers=%d; DesiredNumPublicConnections=%d"), NumberOfPlayers, Subsystem->DesiredNumPublicConnections);
		if (NumberOfPlayers == Subsystem->DesiredNumPublicConnections)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				bUseSeamlessTravel = true;
				World->SeamlessTravel(FString("/Game/Maps/Sandbox?listen"), true);
			}
		}
	} 
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null"));
	}
}