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

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float ForceToAdd = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		float DamageOnHit = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosive")
		float DamageOnExplode = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosive")
		bool IsExplosiveBullet = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile|Explosive")
		float ExplosionRadius = 250.0f;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		class UParticleSystemComponent* VFX;

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

	UFUNCTION()
		void ExplodeBullet(const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
		void HandleHitEvents(const FHitResult& Hit, AActor* OtherActor);
};
