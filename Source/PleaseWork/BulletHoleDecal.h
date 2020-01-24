// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "BulletHoleDecal.generated.h"

/**
 * 
 */
UCLASS()
class PLEASEWORK_API ABulletHoleDecal : public ADecalActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float LifeTime = 10;

	virtual void BeginPlay() override;
};
