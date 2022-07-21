// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime\Engine\Classes\Components\ArrowComponent.h"

#include "EnemySpawner.generated.h"

UCLASS()
class AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Spawn)
	TSubclassOf<AActor> CharacterClass;

	UFUNCTION(BlueprintCallable)
	bool SpawnRandomActors(int count = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<UArrowComponent*> spawnPlaces;
};
