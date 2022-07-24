// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime\Engine\Classes\Camera\CameraComponent.h"
#include "AndroidTestProject/AndroidTestProjectCharacter.h"
#include "Runtime\Engine\Classes\Components\BoxComponent.h"
#include "GameUtils.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

bool AEnemySpawner::SpawnRandomActor()
{
	if (SpawnedActors == MaxActors)
	{
		return false;
	}

	TArray<UPrimitiveComponent*> invisiblePlaces = spawnPlaces.FilterByPredicate([](UPrimitiveComponent* item) { return !item->WasRecentlyRendered(); });

	if (invisiblePlaces.IsEmpty())
	{
		UGameUtils::PrintError(TEXT("Places are empty"), false);
		return false;
	}

	bool result = true;
	int index = FMath::RandRange(0, invisiblePlaces.Num() - 1);

	UPrimitiveComponent* spawnPlace = invisiblePlaces[index];

	FActorSpawnParameters params;
	params.Owner = this;
	params.bNoFail = false;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	FGraphEventRef event = FFunctionGraphTask::CreateAndDispatchWhenReady([this, spawnPlace, &params, &result] {
		for (int j = 0; j < 3; j++)
		{
			if (GetWorld()->SpawnActor<AActor>(CharacterClass, spawnPlace->GetComponentLocation(), FRotator::ZeroRotator, params) == nullptr)
			{
				UGameUtils::PrintError(FString::Printf(TEXT("Failed to spawn actors %d"), j), false);
				result = result || false;
			}
			else
			{
				result = result || true;
				break;
			}
		}
		}, TStatId{}, nullptr, ENamedThreads::GameThread);
	FTaskGraphInterface::Get().WaitUntilTaskCompletes(event);

	if (result)
	{
		ChildIsCreated();
	}
	return result;
}

void AEnemySpawner::ChildIsDestroyed()
{
	SpawnedActors--;
	UGameUtils::Print(FString::Printf(TEXT("spawned actors = %d"), SpawnedActors.load()));
}

void AEnemySpawner::ChildIsCreated()
{
	SpawnedActors++;
	UGameUtils::Print(FString::Printf(TEXT("spawned actors = %d"), SpawnedActors.load()));
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	TArray<USceneComponent*> childrens;
	GetRootComponent()->GetChildrenComponents(false, childrens);

	for (USceneComponent* component : childrens)
	{
		UPrimitiveComponent* place = Cast<UPrimitiveComponent>(component);
		if (place != nullptr)
		{
			spawnPlaces.Add(place);
		}
	}
}
