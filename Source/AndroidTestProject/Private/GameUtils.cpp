// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

void UGameUtils::Print(FString text, bool onScreen)
{
	if (onScreen)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, text);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *text);
	}
}

void UGameUtils::PrintError(FString text, bool onScreen)
{
	if (onScreen)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, text);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *text);
	}
}
