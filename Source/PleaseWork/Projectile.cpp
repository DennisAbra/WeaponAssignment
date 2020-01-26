// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DamageableInterface.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	CollisionComp->SetNotifyRigidBodyCollision(true);
	SetRootComponent(CollisionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(CollisionComp);

	VFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Explosion Effect"));
	VFX->SetupAttachment(CollisionComp);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Mesh->AttachToComponent(CollisionComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Super::BeginPlay();

	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	CollisionComp->AddImpulse(CollisionComp->GetForwardVector() * ForceToAdd, NAME_None, true);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			HandleHitEvents(Hit, OtherActor);
			ExplodeBullet(Hit);
		}
}

void AProjectile::ExplodeBullet(const FHitResult& Hit)
{
	if (IsExplosiveBullet)
	{
		VFX->SetActive(true);
		TArray<FHitResult> OutHits;
		FVector SweepStart = Hit.Location;
		FVector SweepEnd = Hit.Location;

		FCollisionShape ExplosionCol = FCollisionShape::MakeSphere(ExplosionRadius);
		DrawDebugSphere(GetWorld(), Hit.Location, ExplosionCol.GetSphereRadius(), 50, FColor::Purple, false, 2);


		if (GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, ExplosionCol))
		{
			for (auto& Hit : OutHits)
			{
				if (Cast<IDamageableInterface>(Hit.GetActor()))
				{
					Cast<IDamageableInterface>(Hit.GetActor())->ApplyDamage_Implementation(DamageOnExplode);
				}
			}
		}
	}
}

void AProjectile::HandleHitEvents(const FHitResult& Hit, AActor* OtherActor)
{
	if (Cast<IDamageableInterface>(OtherActor)) {
		Cast<IDamageableInterface>(OtherActor)->ApplyDamage_Implementation(DamageOnHit);
		Destroy();
	}

	FRotator rotator = Hit.Normal.Rotation();
	rotator.Pitch -= 90;
	GetWorld()->SpawnActor<ABulletHoleDecal>(BulletHole, Hit.ImpactPoint, rotator);

	DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 2, FColor::Green, true, 10.0f);
	DrawDebugDirectionalArrow(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + (Hit.ImpactNormal * 100), 2.0f, FColor::Green, false, 2	);
	Destroy();
}


