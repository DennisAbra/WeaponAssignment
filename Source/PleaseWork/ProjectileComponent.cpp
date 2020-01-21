// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileComponent.h"
#include "Weapon.h"

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* Parent = GetOwner();
	Owner = Cast<AWeapon>(Parent);
}


// Called every frame
void UProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileComponent::Fire()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Owner->Mesh->GetSocketLocation("Muzzle"), Owner->GetActorRightVector().Rotation(), SpawnParams);
}

