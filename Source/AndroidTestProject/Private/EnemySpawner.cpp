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

bool AEnemySpawner::SpawnRandomActors(int count)
{
	TArray<UPrimitiveComponent*> invisiblePlaces = spawnPlaces.FilterByPredicate([](UPrimitiveComponent* item) { return !item->WasRecentlyRendered(); });

	if (invisiblePlaces.IsEmpty())
	{
		UGameUtils::PrintError(TEXT("Places are empty"));
		return false;
	}

	bool result = true;
	for (int i = 0; i < count; i++)
	{
		int index = FMath::RandRange(0, invisiblePlaces.Num() - 1);

		UPrimitiveComponent* spawnPlace = invisiblePlaces[index];

		FActorSpawnParameters params;
		params.bNoFail = false;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		FGraphEventRef event = FFunctionGraphTask::CreateAndDispatchWhenReady([&i, this, spawnPlace, &params, &result] {
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
	}
	return result;
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
