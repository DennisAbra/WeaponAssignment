// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoilComponent.h"
#include "Weapon.h"
#include "MyProjectCharacter.h"
#include "TimerManager.h"

// Sets default values for this component's properties
URecoilComponent::URecoilComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Temp = GetOwner();
	Owner = Cast<AWeapon>(Temp);
}


// Called every frame
void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsRecoiling)
	{
		FinalRecoilPitch = RecoilMultiplier * FMath::FRandRange(MinPitchRange, MaxPitchRange);
		FinalRecoilYaw = RecoilMultiplier * FMath::FRandRange(MinYawRange, MaxYawRange);

		Owner->Owner->AddControllerPitchInput(FinalRecoilPitch);
		Owner->Owner->AddControllerYawInput(FinalRecoilYaw);
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void URecoilComponent::StopRecoil()
{
	IsRecoiling = false;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void URecoilComponent::StartRecoil()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URecoilComponent::StopRecoil, RecoilTime, true);
	IsRecoiling = true;
}

