// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "TargetManager.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	hideLocation = GetActorLocation() + FVector::DownVector * 200;
	showLocation = GetActorLocation();
	Hide();
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::Hide()
{
	SetActorEnableCollision(false);
	currentHealth = 0;
	SetActorLocation(hideLocation);
	isShown = false;
}

void ATarget::Show()
{
	SetActorEnableCollision(true);
	currentHealth = maxHealth;
	SetActorLocation(showLocation);
	isShown = true;
}

float ATarget::ApplyDamage_Implementation(float InDamage)
{
	if (currentHealth > 0)
	{
		currentHealth -= InDamage;
		targetManager->DisplayDamage(GetActorLocation(), FString::FromInt(FMath::RoundToInt(InDamage)));
	}
	if (currentHealth <= 0.0f) {
		Hide();
	}


	return currentHealth;
}


