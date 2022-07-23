// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtils.generated.h"

/**
 * 
 */
UCLASS()
class UGameUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void Print(FString text, bool onScreen = true);
	static void PrintError(FString text, bool onScreen = true);
};
