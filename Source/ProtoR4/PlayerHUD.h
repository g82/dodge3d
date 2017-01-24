// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class APlayerHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	virtual void PostRender() OVERRIDE;
	virtual void DrawHUD() OVERRIDE;
	virtual void BeginPlay() OVERRIDE;

private:
	UPROPERTY()
		FVector MouseWorldPosition;
	
};
