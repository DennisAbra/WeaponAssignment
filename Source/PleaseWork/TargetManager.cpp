// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetManager.h"
#include <Engine.h>

// Sets default values
ATargetManager::ATargetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATargetManager::DisplayDamage(FVector location, FString text)
{
	ADamageDisplay* damageDisplay = nullptr;
	for (int32 i = 0; i < damageDisplays.Num(); i++)
	{
		if (!damageDisplays[i]->bDisplayed) {
			damageDisplay = damageDisplays[i];
			break;
		}
	}
	if (damageDisplay != nullptr)
		damageDisplay->Display(location, text);
}

// Called when the game starts or when spawned
void ATargetManager::BeginPlay()
{
	Super::BeginPlay();

	targets.Init(nullptr, spawnPoints.Num());
	damageDisplays.Init(nullptr, displayPoolSize);

	UWorld* const World = GetWorld();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < spawnPoints.Num(); i++) {
		targets[i] = World->SpawnActor<ATarget>(spawnClass, spawnPoints[i]->GetActorLocation(), spawnPoints[i]->GetActorRotation(), ActorSpawnParams);
		targets[i]->targetManager = this;
	}
	for (int32 i = 0; i < damageDisplays.Num(); i++) {
		damageDisplays[i] = World->SpawnActor<ADamageDisplay>(displayClass);
	}
}

// Called every frame
void ATargetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int targetsShown = 0;
	for (int32 i = 0; i < targets.Num(); i++)
	{
		if (targets[i]->isShown) {
			targetsShown++;
			if (targetsShown >= targetsAtOnce)
				return;
		}
	}

	if (currentSpawnTime <= 0) {

		currentSpawnTime = timeUntilSpawn;

		ATarget* target = nullptr;

		while (target == nullptr)
		{
			target = targets[FMath::RandRange(0, targets.Num() - 1)];

			if (target->isShown)
				target = nullptr;
		}
		target->Show();
	}
	else {
		currentSpawnTime -= DeltaTime;
	}
}

