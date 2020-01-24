// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDisplay.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
void ADamageDisplay::Display(FVector location, FString text)
{
	SetActorLocation(location + FVector::UpVector * 185);
	SetActorHiddenInGame(false);
	bDisplayed = true;
	CurrentLifeTime = LifeTime;
	TextField->SetText("-" + text);
}

void ADamageDisplay::Vanish()
{
	SetActorHiddenInGame(true);
	bDisplayed = false;
}

// Sets default values
ADamageDisplay::ADamageDisplay()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TextField = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

}

// Called when the game starts or when spawned
void ADamageDisplay::BeginPlay()
{
	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	TextField->TextRenderColor = FColor::White;
	TextField->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	SetActorScale3D(FVector::OneVector * 2);

	Super::BeginPlay();
	Vanish();
}

// Called every frame
void ADamageDisplay::Tick(float DeltaTime)
{
	if (!bDisplayed)
		return;
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector::UpVector * SoarSpeed * DeltaTime);

	CurrentLifeTime -= DeltaTime;
	if (CurrentLifeTime <= 0)
		Vanish();

	if (PlayerActor != nullptr)
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerActor->GetActorLocation()));

}

