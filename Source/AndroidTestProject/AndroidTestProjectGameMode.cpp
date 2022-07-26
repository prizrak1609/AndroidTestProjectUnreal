// Copyright Epic Games, Inc. All Rights Reserved.

#include "AndroidTestProjectGameMode.h"
#include "AndroidTestProjectPlayerController.h"
#include "AndroidTestProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAndroidTestProjectGameMode::AAndroidTestProjectGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAndroidTestProjectPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

int32 AAndroidTestProjectGameMode::GetNumPlayers()
{
	return 1;
}

int32 AAndroidTestProjectGameMode::GetNumSpectators()
{
	return 0;
}
