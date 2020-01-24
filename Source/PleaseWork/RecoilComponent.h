// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoilComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASEWORK_API URecoilComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinPitchRange = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxPitchRange = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MinYawRange = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float MaxYawRange = 1.0f;
	/**
	 * Works as a multiplier
	 * Recommended value is between 0.1 - 0.5
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recoil")
		float RecoilMultiplier = 1;
	/**
	 * How long should the weapon recoil?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recoil")
		float RecoilTime = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Recoil")
		bool IsRecoiling = false;

	float FinalRecoilPitch;
	float FinalRecoilYaw;

	class AWeapon* Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void StopRecoil();
	void StartRecoil();
		
};
