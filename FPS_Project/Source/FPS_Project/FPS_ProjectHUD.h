// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "FPS_ProjectHUD.generated.h"

UCLASS()
class AFPS_ProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPS_ProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

