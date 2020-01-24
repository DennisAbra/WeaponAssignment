// Fill out your copyright notice in the Description page of Project Settings.


#include "BurstComponent.h"
#include "Weapon.h"
#include "MyProjectCharacter.h"
#include "HitscanComponent.h"
#include "ProjectileComponent.h"

// Sets default values for this component's properties
UBurstComponent::UBurstComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBurstComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Parent = GetOwner();
	Owner = Cast<AWeapon>(Parent);
	
}

void UBurstComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Probably not necessary, can just add the recoilcomponent instead
	//If u want to use it, turn on tick
	if (bIsBursting)
	{
		FinalBurstPitch = Burst * FMath::FRandRange(MinPitchRange, MaxPitchRange);
		FinalBurstYaw = Burst * FMath::FRandRange(MinYawRange, MaxYawRange);

		Owner->Owner->AddControllerPitchInput(FinalBurstPitch);
		Owner->Owner->AddControllerYawInput(FinalBurstYaw);
	}
}

void UBurstComponent::Fire()
{
	StopBurst();
	Owner->Fire();
}

void UBurstComponent::StopBurst()
{
	bIsBursting = false;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UBurstComponent::StartBurst()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBurstComponent::Fire, TimeUntillNextBurstShot, true);
	bIsBursting = true;
}


