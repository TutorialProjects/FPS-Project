// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPS_Project.h"
#include "FPS_ProjectGameMode.h"
#include "FPS_ProjectHUD.h"
#include "Player/FirstPersonCharacter.h"

AFPS_ProjectGameMode::AFPS_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPS_ProjectHUD::StaticClass();
}
