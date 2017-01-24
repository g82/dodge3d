// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ProtoR4PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AProtoR4PlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	virtual void SetupInputComponent() OVERRIDE;
	
	UFUNCTION()
	void MoveUp(float pValue);

	UFUNCTION()
	void MoveRight(float pValue);

	UFUNCTION()
	void LeftMouseClick();

	UFUNCTION()
	void LeftMouseRelease();
};
