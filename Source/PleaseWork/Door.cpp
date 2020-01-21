// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

ADoor::ADoor()
{
	bReplicates = true;
	GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetSkeletalMeshComponent()->SetCollisionProfileName("NoCollision");
}

void ADoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("OnConstruction script"));
	if (AnimationOnOpenClose)
	{
		USkeletalMeshComponent* MeshComp = GetSkeletalMeshComponent();
		float PlayRate = IsOpen ? 1.0f : -1.0f;
		float Length = PlayRate * AnimationOnOpenClose->GetPlayLength();
		UE_LOG(LogTemp, Warning, TEXT("OnConstruction %f %d"), Length, IsOpen);
		MeshComp->OverrideAnimationData(AnimationOnOpenClose, false, true, Length, PlayRate);
	}
}

void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADoor, IsOpen);
}

void ADoor::OnRep_IsOpen(bool bOldIsOpen)
{
}
