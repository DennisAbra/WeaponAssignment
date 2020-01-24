// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "HitscanComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASEWORK_API UHitscanComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHitscanComponent();
	class AWeapon* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootingDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamagePerShot = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BulletSpreadDegrees = 0.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		FHitResult Fire();

	FVector GetBulletSpread();
};
