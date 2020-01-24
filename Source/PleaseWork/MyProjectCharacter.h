// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyProjectCharacter.generated.h"

UCLASS()
class PLEASEWORK_API AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY() 
		/** Pawn mesh: 1st person view (arms; seen only by self) */


	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	//My Lines
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* PickUpCollider;

	UPROPERTY(VisibleAnywhere, Category = "Armory")
		TArray<class AWeapon*> armory;

	UPROPERTY(VisibleAnywhere, Category = "Armory")
		int armoryIndex;

	bool ArmoryFull();
	void ScrollArmory(float direction);
	void ChangeWeapon(float direction, bool droppedWeapon = false);
	void AddWeapon(AWeapon* weapon);

	UFUNCTION(BlueprintCallable)
		class AWeapon* CurrentWeapon();
public:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armory")
		int armorySize = 3;

public:
	AMyProjectCharacter();

protected:
	virtual void BeginPlay();


public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Mesh1P;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Disarm")
		float ThrowMultiplier = 800;

protected:
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	int ShotsFired = 0;

	/** Fires a projectile. */
	void OnFire();

	//Fires continously
	void Fire(float Value);
	void TryToReload();

	void DropCurrentWeapon();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/*
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
