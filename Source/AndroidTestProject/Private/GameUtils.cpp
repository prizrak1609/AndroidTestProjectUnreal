// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

void UGameUtils::Print(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, text);
}

void UGameUtils::PrintError(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, text);
}
