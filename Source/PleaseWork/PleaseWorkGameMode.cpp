// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PleaseWorkGameMode.h"
#include "PleaseWorkHUD.h"
#include "PleaseWorkCharacter.h"
#include "UObject/ConstructorHelpers.h"

APleaseWorkGameMode::APleaseWorkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APleaseWorkHUD::StaticClass();
}
