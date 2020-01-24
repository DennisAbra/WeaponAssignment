// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletHoleDecal.h"
#include "Projectile.generated.h"

UCLASS()
class PLEASEWORK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AProjectile();

	/**
	 * The root component. A Hit event is connected to this collider
	 * If you wish to use another collider type for OnHitEvents you need to turn of collision for this collider in the inspector
	 * Create a new collider and add OnHit event in blueprints
	 * When OnHit is called, connect it to HandleHitEvents && ExplodeBullet
	 */
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;
	/**
	 * Defines the force that pushed the projectile out from the weapon
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float ForceToAdd = 500.0f;
	/**
	 * Defines the damage on a direct hit
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float DamageOnHit = 10.0f;
	/**
	 * Defines the damage on explosion
	 * Only applicable when IsExplosiveBullet is set to true
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosive")
		float DamageOnExplode = 15.0f;
	/**
	 * If true bullets will explode on impact
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosive")
		bool IsExplosiveBullet = false;
	/**
	 * Radius of the explosion
	 * Only applicable if IsExplosiveBullet is set to true
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosive")
		float ExplosionRadius = 250.0f;
	/**
	 * Set the Explosion visual effect
	 * Only applicable if IsExplosiveBullet is set to true
	 */
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		class UParticleSystemComponent* VFX;
	/**
	 * Defines a Decal to spawn on the collisionImpact
	 * Works about 30-40% of the time
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABulletHoleDecal> BulletHole;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherACtor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	/**
	 * Explode bullets on collision impact if IsExplosiveBullet is set to true
	 * Call with HandleHitEvents if you wish the projectile to have an impact damage along with the AOE explosion
	 */
	UFUNCTION(BlueprintCallable)
		void ExplodeBullet(const FHitResult& Hit);
	/**
	 * Handle all HitEvents for a normal projectile that is not explosive
	 */
	UFUNCTION(BlueprintCallable)
		void HandleHitEvents(const FHitResult& Hit, AActor* OtherActor);
};
