// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "Animation/AnimSequence.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class PLEASEWORK_API ADoor : public ASkeletalMeshActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
		UAnimSequence* AnimationOnOpenClose = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_IsOpen, Category = "Door")
	bool IsOpen = false;

	ADoor();
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
		void OnRep_IsOpen(bool bOldIsOpen);
};
