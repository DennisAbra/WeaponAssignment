// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletHoleDecal.h"
#include "Components/DecalComponent.h"

void ABulletHoleDecal::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = false;
	SetLifeSpan(LifeTime);
	Super::BeginPlay();
}