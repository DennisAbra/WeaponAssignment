// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScopeComponent.generated.h"

class AController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEASEWORK_API UScopeComponent : public UActorComponent
{
	GENERATED_BODY()

	float BaseFOV;

public:	
	// Sets default values for this component's properties
	UScopeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Zoom)
		float ZoomValue = 0.f;

	UFUNCTION(BlueprintCallable)
		void ZoomIn(AController* Control);

	UFUNCTION(BlueprintCallable)
		void ZoomOut(AController* Control);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
