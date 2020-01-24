// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "DamageDisplay.generated.h"

UCLASS()
class PLEASEWORK_API ADamageDisplay : public AActor
{
	GENERATED_BODY()

	void Vanish();

	float CurrentLifeTime;

	class UTextRenderComponent* TextField;

	class APawn* PlayerActor = nullptr;

public:
	// Sets default values for this actor's properties
	ADamageDisplay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float LifeTime = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float SoarSpeed = 2;

	bool bDisplayed;

	void Display(FVector location, FString text);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
