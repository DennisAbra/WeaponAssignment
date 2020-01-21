// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDisplay.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
void ADamageDisplay::Display(FVector location, FString text)
{
	SetActorLocation(location + FVector::UpVector * 185);
	SetActorHiddenInGame(false);
	displayed = true;
	currentLifeTime = lifeTime;
	textField->SetText("-" + text);
}

void ADamageDisplay::Vanish()
{
	SetActorHiddenInGame(true);
	displayed = false;
}

// Sets default values
ADamageDisplay::ADamageDisplay()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	textField = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

}

// Called when the game starts or when spawned
void ADamageDisplay::BeginPlay()
{
	playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	textField->TextRenderColor = FColor::White;
	textField->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	SetActorScale3D(FVector::OneVector * 2);

	Super::BeginPlay();
	Vanish();
}

// Called every frame
void ADamageDisplay::Tick(float DeltaTime)
{
	if (!displayed)
		return;
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector::UpVector * soarSpeed * DeltaTime);

	currentLifeTime -= DeltaTime;
	if (currentLifeTime <= 0)
		Vanish();

	if (playerActor != nullptr)
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerActor->GetActorLocation()));

}

