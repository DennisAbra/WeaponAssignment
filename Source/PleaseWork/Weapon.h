// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "BulletHoleDecal.h"
#include "RecoilComponent.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EFireTypeEnum : uint8
{
	FTSemi UMETA(DisplayName = "SemiAutomatic"),
	FTBurst UMETA(DisplayName = "BurstFire"),
	FTAutomatic UMETA(DisplayName = "FullyAutomatic")
};

UCLASS()
class PLEASEWORK_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Visual Feedback")
		UParticleSystemComponent* VFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Feedback")
		TSubclassOf<ABulletHoleDecal> BulletHole;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Fire Rate")
		float TimeUntillNextShot = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Burst - VALUES ONLY USED WHEN FIRETYPE IS SET TO BURST")
		float TimeUntilNextBurstShot = 0.09f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Burst - VALUES ONLY USED WHEN FIRETYPE IS SET TO BURST")
		int BulletsPerBurst = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		bool CanShoot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Type of Shooting")
		EFireTypeEnum FireType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
		UPhysicsAsset* PhysicsAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		int CurrentAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		int MaxAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		bool InfiniteAmmo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		float ReloadTime = 1.0f;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	bool IsReloading = false;
	class AMyProjectCharacter* Owner;

	bool HasFiredBurst = false;
	int BurstShotFired = 1;
	bool IsBursting = false;
	 URecoilComponent* RecoilComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle;
	FTimerHandle BurstHandle;
	FTimerDelegate TimerDelegate;

	class UHitscanComponent* HitScanComp;
	class UProjectileComponent* ProjectileComp;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AWeapon();

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
		void Fire();

	void HandleBurstExitConditions();

	void HandleShootingComponents();

	void HandleCooldownBetweenShots();

	void PlayFireSFX();
	void PlayFireAnimation();

	UFUNCTION(BlueprintCallable)
		void Reload();

	UFUNCTION(BlueprintCallable)
	void StartReloadTimer();

	UFUNCTION(BlueprintCallable)
	void StartBurstTimer();
};
