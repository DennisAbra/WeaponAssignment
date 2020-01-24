// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectCharacter.h"
#include "Weapon.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

AMyProjectCharacter::AMyProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	//My lines
	PickUpCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	PickUpCollider->SetSimulatePhysics(false);
	PickUpCollider->SetNotifyRigidBodyCollision(true);
	PickUpCollider->BodyInstance.SetCollisionProfileName("OverlapAll");

	PickUpCollider->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

bool AMyProjectCharacter::ArmoryFull()
{
	for (int32 i = 0; i < armory.Num(); i++)
	{
		if (armory[i] == nullptr)
		{
			return false;
		}
	}
	return true;
}

void AMyProjectCharacter::ScrollArmory(float direction)
{
	ChangeWeapon(direction);
}

void AMyProjectCharacter::ChangeWeapon(float direction, bool droppedWeapon)
{
	if (direction != 0)
	{
		int requiredAmount = droppedWeapon ? 1 : 2;
		int armoryAmount = 0;
		for (int32 i = 0; i < armory.Num(); i++) {
			if (armory[i] != nullptr)
				armoryAmount++;
		}
		if (armoryAmount < requiredAmount)
			return;
		if (CurrentWeapon() != nullptr)
			CurrentWeapon()->Mesh->SetVisibility(false);

		do {
			armoryIndex += direction;

			if (armoryIndex >= armory.Num())
				armoryIndex = 0;
			else if (armoryIndex < 0)
				armoryIndex = armory.Num() - 1;
		} while (CurrentWeapon() == nullptr);

		if (CurrentWeapon() != nullptr)
			CurrentWeapon()->Mesh->SetVisibility(true);
	}
}

void AMyProjectCharacter::AddWeapon(AWeapon* weapon)
{
	for (int32 i = 0; i < armory.Num(); i++)
	{
		if (armory[i] == nullptr) {
			armory[i] = weapon;
			armory[i]->Mesh->SetSimulatePhysics(false);
			armory[i]->BoxCollider->SetActive(false);
			if (armoryIndex != i)
				armory[i]->Mesh->SetVisibility(false);
			break;
		}
	}
}

class AWeapon* AMyProjectCharacter::CurrentWeapon()
{
	if (armory.Num() > 0)
		return armory[armoryIndex];
	else return nullptr;
}

void AMyProjectCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->Tags.Contains("Weapon") && !ArmoryFull())
		{
			AddWeapon(Cast<AWeapon>(OtherActor));
			OtherActor->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "GripPoint");
			OtherActor->SetActorTransform(Mesh1P->GetSocketTransform("GripPoint"));

			Cast<AWeapon>(OtherActor)->SetOwner(this);
			Cast<AWeapon>(OtherActor)->Owner = this;
		}
	}
}


void AMyProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Mesh1P->SetHiddenInGame(false, true);
	PickUpCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectCharacter::OnBeginOverlap);

	armory.Init(nullptr, armorySize);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	//Drop Weapon
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &AMyProjectCharacter::DropCurrentWeapon);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyProjectCharacter::OnFire);
	PlayerInputComponent->BindAxis("FireAxis", this, &AMyProjectCharacter::Fire);

	PlayerInputComponent->BindAxis("Scroll", this, &AMyProjectCharacter::ScrollArmory);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyProjectCharacter::TryToReload);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyProjectCharacter::LookUpAtRate);
}

void AMyProjectCharacter::OnFire()
{
	// Use for semi
	if (CurrentWeapon() && CurrentWeapon()->CanShoot && CurrentWeapon()->FireType == EFireTypeEnum::FTSemi)
	{
		CurrentWeapon()->Fire();
	}
}

void AMyProjectCharacter::Fire(float Value)
{
	if (CurrentWeapon() && CurrentWeapon()->CanShoot)
	{
		if (CurrentWeapon()->FireType == EFireTypeEnum::FTAutomatic && Value != 0)
		{
			CurrentWeapon()->Fire();
		}
		else if (CurrentWeapon()->FireType == EFireTypeEnum::FTBurst && Value != 0)
		{
			if (!CurrentWeapon()->HasFiredBurst)
			{
				CurrentWeapon()->StartBurstTimer();
			}
		}
	}
}

void AMyProjectCharacter::TryToReload()
{
	CurrentWeapon()->StartReloadTimer();
}


void AMyProjectCharacter::DropCurrentWeapon()
{
	if (CurrentWeapon())
	{
		if (CurrentWeapon()->RecoilComp)
		{
			CurrentWeapon()->RecoilComp->StopRecoil();
		}
		//Make sure the weapon gets effected by gravity
		CurrentWeapon()->Owner = nullptr;
		CurrentWeapon()->Mesh->SetSimulatePhysics(true);
		CurrentWeapon()->Mesh->SetVisibility(true);
		CurrentWeapon()->BoxCollider->SetActive(true);
		CurrentWeapon()->DetachRootComponentFromParent();
		CurrentWeapon()->Mesh->AddImpulse(CurrentWeapon()->Mesh->GetRightVector() * ThrowMultiplier, NAME_None, true);
		armory[armoryIndex] = nullptr;


		for (int32 i = armoryIndex; i < armory.Num() - 1; i++)
		{
			if (armory[i + 1] != nullptr) {
				armory[i] = armory[i + 1];
				armory[i + 1] = nullptr;
			}
		}
		if (CurrentWeapon() != nullptr)
			CurrentWeapon()->Mesh->SetVisibility(true);
		else
			ChangeWeapon(-1, true);
	}
}

void AMyProjectCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyProjectCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

