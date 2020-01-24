// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanComponent.h"
#include "Weapon.h"
#include "DamageableInterface.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UHitscanComponent::UHitscanComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHitscanComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Parent = GetOwner();
	Owner = Cast<AWeapon>(Parent);
}


// Called every frame
void UHitscanComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FHitResult UHitscanComponent::Fire()
{
	FVector Location;
	FRotator Rotation;
	FHitResult Hit;

	//Change this to something more abstract
	Location = Owner->Mesh->GetSocketLocation("Muzzle");
	Rotation = Owner->Mesh->GetSocketRotation("Muzzle");

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() + (GetBulletSpread() * ShootingDistance));

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility))
	{
		if (Cast<IDamageableInterface>(Hit.GetActor()))
		{
			UE_LOG(LogTemp, Display, TEXT("TASKADA"));
			Cast<IDamageableInterface>(Hit.GetActor())->Execute_ApplyDamage(Hit.GetActor(), DamagePerShot);
		}
	}

	return Hit;
}

FVector UHitscanComponent::GetBulletSpread()
{
	return UKismetMathLibrary::RandomUnitVectorInConeInDegrees(GetOwner()->GetActorRightVector(), BulletSpreadDegrees);
}

