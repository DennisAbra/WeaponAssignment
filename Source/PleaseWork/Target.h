// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageableInterface.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class PLEASEWORK_API ATarget : public AActor, public IDamageableInterface
{
	GENERATED_BODY()

	FVector hideLocation;
	FVector showLocation;

	float currentHealth;

public:

	class ATargetManager* targetManager;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float maxHealth = 10.0f;

	bool isShown;
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Hide();
	void Show();

	virtual float ApplyDamage_Implementation(float InDamage) override;

};
