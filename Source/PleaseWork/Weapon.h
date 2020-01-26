// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "BulletHoleDecal.h"
#include "RecoilComponent.h"
#include "ScopeComponent.h"
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
	/**
	 * Sets the time to wait until next bullet can be shot
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Fire Rate")
		float TimeUntillNextShot = 0.1f;
	/**
	 * Sets the time to wait until next bullet in the burst can be shot
	 * Only used if FireType is set to Burst
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Burst - VALUES ONLY USED WHEN FIRETYPE IS SET TO BURST")
		float TimeUntilNextBurstShot = 0.09f;

	/**
	* Sets the amount of bullets to be shot in a burst
	* Only used if FireType is set to Burst
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Burst - VALUES ONLY USED WHEN FIRETYPE IS SET TO BURST")
		int BulletsPerBurst = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		bool CanShoot = true;

	/**
	 * Defines how firing a weapon works.
	 * Burst = x amount of bullets shot in a burst
	 * Semi = 1 click 1 shot
	 * Automatic = Shoots while button is held down
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Type of Shooting")
		EFireTypeEnum FireType;

	/**
	 * Amount of bullets currently in the magazine
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		int CurrentAmmo = 30;

	/**
	 * Total amount of bullets in the magazine
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		int MaxAmmo = 30;
	/**
	 * Can fire indefinitely without the need to reload
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		bool InfiniteAmmo = false;
	/**
	 * Sets the time we need to wait after all bullets in a magazine has run out
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Ammo")
		float ReloadTime = 1.0f;

	/**
	 * Sets the sound that plays when shooting
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;
	
	/**
	 * Sets the animationMonage that will play when firing
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(BlueprintReadOnly)
		bool IsReloading = false;
	/**
	 * Owner of the weapon
	 */
	class AMyProjectCharacter* Owner;

	bool HasFiredBurst = false;
	int BurstShotFired = 1;
	bool bIsBursting = false;
	 URecoilComponent* RecoilComp;
	 class UScopeComponent* ScopeComp;


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
	/**
	 * Reloads the gun that is currently equppied
	 */
	UFUNCTION(BlueprintCallable)
		void Reload();
	/**
	* Starts the reloadTimer. When the timer is up Reload will be called
	*/
	UFUNCTION(BlueprintCallable)
	void StartReloadTimer();

	/**
	 * Starts the burst timer. It will go through and shoot a pre assigned amount of bullets and wait a pre assigned time between each one.
	 First bullet is shot instantly
	 */
	UFUNCTION(BlueprintCallable)
	void StartBurstTimer();
};
