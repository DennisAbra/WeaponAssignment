// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DamageableInterface.h"
#include "DrawDebugHelpers.h"

AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	CollisionComp->SetNotifyRigidBodyCollision(true);
	SetRootComponent(CollisionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(CollisionComp);
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

//void AProjectile::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
//	{
//		if (Cast<IDamageableInterface>(OtherActor)) {
//			Cast<IDamageableInterface>(OtherActor)->Execute_ApplyDamage(OtherActor, 3);
//			Destroy();
//		}
//
//		//if (OtherComp->IsSimulatingPhysics()) {
//		//	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
//		//	Destroy();
//		//}
//		FRotator rotator = SweepResult.Normal.Rotation();
//		rotator.Pitch -= 90;
//		GetWorld()->SpawnActor<ABulletHoleDecal>(BulletHole, SweepResult.ImpactPoint, rotator);
//		
//	}
//}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			if (Cast<IDamageableInterface>(OtherActor)) {
				Cast<IDamageableInterface>(OtherActor)->Execute_ApplyDamage(OtherActor, 3);
				Destroy();
			}

			//if (OtherComp->IsSimulatingPhysics()) {
			//	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			//	Destroy();
			//}
			FRotator rotator = Hit.Normal.Rotation();
			rotator.Pitch -= 90;
			GetWorld()->SpawnActor<ABulletHoleDecal>(BulletHole, Hit.ImpactPoint, rotator);

			DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 2, FColor::Green, true, 10.0f);
			DrawDebugDirectionalArrow(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + (Hit.ImpactNormal * 100), 2.0f, FColor::Green, true, 10);

		}
}


