// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DamageableInterface.h"
#include "HitscanComponent.h"
#include "ProjectileComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyProjectCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(Mesh);

	VFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	VFX->SetupAttachment(Mesh);

	RootComponent = Mesh;
}

void AWeapon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Mesh->SetOnlyOwnerSee(false);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;
	Mesh->SetCollisionProfileName("WeaponMesh");
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);

	BoxCollider->SetSimulatePhysics(false);
	BoxCollider->SetNotifyRigidBodyCollision(true);
	BoxCollider->BodyInstance.SetCollisionProfileName("Weapon");
	BoxCollider->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);

	VFX->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "Muzzle");
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	// CheckStartParamaters
	if (!this->ActorHasTag("Weapon"))
	{
		this->Tags.Add("Weapon");
	}

	if (TimeUntillNextShot < 0.001f)
	{
		TimeUntillNextShot = 0.001f;
		UE_LOG(LogTemp, Warning, TEXT("TimeUntillNextShot Can't be 0 or lower"));
	}

	if (TimeUntilNextBurstShot < 0.001f)
	{
		TimeUntilNextBurstShot = 0.001f;
		UE_LOG(LogTemp, Warning, TEXT("TimeUntillBurst Can't be 0 or lower"));
	}
	//
	HitScanComp = FindComponentByClass<UHitscanComponent>();

	ProjectileComp = FindComponentByClass<UProjectileComponent>();

	RecoilComp = FindComponentByClass<URecoilComponent>();

	ScopeComp = FindComponentByClass<UScopeComponent>();

	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Fire()
{
	HandleBurstExitConditions();

	if (CurrentAmmo > 0 && !IsReloading || InfiniteAmmo)
	{
		HandleShootingComponents();
		HandleCooldownBetweenShots();
		CurrentAmmo--;
	}
	else
	{
		StartReloadTimer();
	}
}

void AWeapon::HandleBurstExitConditions()
{
	//HandleBurstExitConditions
	if (FireType == EFireTypeEnum::FTBurst && bIsBursting)
	{
		BurstShotFired++;
	}

	if (BurstShotFired == BulletsPerBurst && !HasFiredBurst || Owner == nullptr)
	{
		GetWorldTimerManager().ClearTimer(BurstHandle);
		HasFiredBurst = true;
		BurstShotFired = 1;
	}
}

void AWeapon::HandleShootingComponents()
{
	if (HitScanComp)
	{
		FHitResult Result = HitScanComp->Fire();

		if (Result.bBlockingHit) {

			FVector location = Result.ImpactPoint;
			FRotator rotator = Result.Normal.Rotation();
			rotator.Pitch -= 90;

			GetWorld()->SpawnActor<ABulletHoleDecal>(BulletHole, location, rotator);
		}
		VFX->ActivateSystem(true);
	}

	if (ProjectileComp)
	{
		ProjectileComp->Fire();
		VFX->ActivateSystem(true);
	}

	if (RecoilComp)
	{
		RecoilComp->StartRecoil();
	}
}

void AWeapon::HandleCooldownBetweenShots()
{
	if ((FireType == EFireTypeEnum::FTBurst && HasFiredBurst) || FireType != EFireTypeEnum::FTBurst)
	{
		TimerDelegate.BindLambda([this]()
		{
			bIsBursting = false;
			CanShoot = true;
			HasFiredBurst = false;
		});

		CanShoot = false;
		if (!CanShoot)
		{
			GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, TimeUntillNextShot, false);
		}
	}
}


void AWeapon::PlayFireSFX()
{
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void AWeapon::PlayFireAnimation()
{
	if (FireAnimation != NULL)
	{
		UAnimInstance* AnimInstance = Cast<AMyProjectCharacter>(GetOwner())->Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}


void AWeapon::StartReloadTimer()
{
	if (!IsReloading)
	{
		IsReloading = true;
		FTimerHandle ReloadHandle;
		GetWorldTimerManager().SetTimer(ReloadHandle, this, &AWeapon::Reload, ReloadTime, false);
	}
}

void AWeapon::Reload()
{
	CurrentAmmo = MaxAmmo;
	HasFiredBurst = false;
	CanShoot = true;
	IsReloading = false;
	bIsBursting = false;
}

void AWeapon::StartBurstTimer()
{
	if (!bIsBursting)
	{
		Fire();
		bIsBursting = true;
		GetWorldTimerManager().SetTimer(BurstHandle, this, &AWeapon::Fire, TimeUntilNextBurstShot, true);
	}
}


