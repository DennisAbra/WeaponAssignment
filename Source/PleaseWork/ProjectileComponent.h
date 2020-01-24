// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "ProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASEWORK_API UProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileComponent();

	class AWeapon* Owner;
	/**
	 * Sets the projectile to spawn when we shoot
	 * Should be an existing blueprint of the Projectile class
	 */
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Projectile")
		TSubclassOf<AProjectile> ProjectileToSpawn;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void Fire();
		
};
