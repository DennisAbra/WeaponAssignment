// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BurstComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASEWORK_API UBurstComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBurstComponent();
	class AWeapon* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeUntillNextBurstShot = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int BulletsPerBurst = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		float MinPitchRange = -1.0f;						
															
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		float MaxPitchRange = -1.0f;						
															
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		float MinYawRange = -1.0f;							
															
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		float MaxYawRange = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burst")
		float Burst = -1.0f;

	int ShotsFired = 0;
	float FinalBurstPitch;
	float FinalBurstYaw;
	bool bIsBursting = false;
	FTimerHandle TimerHandle;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	void Fire();
	void StopBurst();
	void StartBurst();
};
