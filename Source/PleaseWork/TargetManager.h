// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.h"
#include "DamageDisplay.h"
#include "TargetManager.generated.h"

UCLASS()
class PLEASEWORK_API ATargetManager : public AActor
{
	GENERATED_BODY()
	
	float currentSpawnTime;

	TArray<class ATarget*> targets;

	TArray<class ADamageDisplay*> damageDisplays;

public:
	// Sets default values for this actor's properties
	ATargetManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TSubclassOf<ATarget> spawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		int targetsAtOnce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		float timeUntilSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TArray<class ATargetPoint*> spawnPoints;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Display")
		TSubclassOf<ADamageDisplay> displayClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Display")
		int displayPoolSize;

	void DisplayDamage(FVector location, FString text);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
