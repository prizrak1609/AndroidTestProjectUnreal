// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AndroidTestProjectGameMode.generated.h"

UCLASS(minimalapi)
class AAndroidTestProjectGameMode final : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAndroidTestProjectGameMode();

	int32 GetNumPlayers() override;

	int32 GetNumSpectators() override;
};
