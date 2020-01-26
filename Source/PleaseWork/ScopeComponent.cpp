// Fill out your copyright notice in the Description page of Project Settings.


#include "ScopeComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "MyProjectCharacter.h"

// Sets default values for this component's properties
UScopeComponent::UScopeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UScopeComponent::ZoomIn(AController * Control)
{
	if (Cast<APlayerController>(Control))
	{
		APlayerController* MyController = Cast<APlayerController>(Control);

		UCameraComponent* MyCamera = Cast<AMyProjectCharacter>(MyController->GetPawn())->GetFirstPersonCameraComponent();

		BaseFOV = MyCamera->FieldOfView;

		MyCamera->FieldOfView = ZoomValue;

	}
}

void UScopeComponent::ZoomOut(AController * Control)
{
	if (Cast<APlayerController>(Control))
	{
		APlayerController* MyController = Cast<APlayerController>(Control);

		UCameraComponent* MyCamera = Cast<AMyProjectCharacter>(MyController->GetPawn())->GetFirstPersonCameraComponent();

		MyCamera->FieldOfView = BaseFOV;

	}
}


// Called when the game starts
void UScopeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScopeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

