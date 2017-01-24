// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProtoR4.h"
#include "ProtoR4PlayerController.h"

#include "PlayerCamera.h"
#include "PlayerCharacter.h"

AProtoR4PlayerController::AProtoR4PlayerController(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	PlayerCameraManagerClass = APlayerCamera::StaticClass();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AProtoR4PlayerController::SetupInputComponent()
{	
	
	/*for (auto Iter = CurrentInputStack.CreateConstIterator(); Iter; ++Iter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("CurrentInputStack"));
	}*/
	
	if (InputComponent == NULL)
	{
		/** create & register InputComponent */
		InputComponent = ConstructObject<UInputComponent>(UInputComponent::StaticClass(), this, TEXT("PC_InputComponent()"));
		InputComponent->RegisterComponent();
		
		BIND_AXIS(InputComponent, "MoveUp", &AProtoR4PlayerController::MoveUp);
		BIND_AXIS(InputComponent, "MoveRight", &AProtoR4PlayerController::MoveRight);

		BIND_ACTION(InputComponent, "LeftMouseButton", IE_Pressed, &AProtoR4PlayerController::LeftMouseClick);
		BIND_ACTION(InputComponent, "LeftMouseButton", IE_Released, &AProtoR4PlayerController::LeftMouseRelease);
	}
}

void AProtoR4PlayerController::MoveUp(float pValue)
{
	/*if (GEngine && (pValue != 0.f))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("AProtoR4PlayerController::MoveUp"));
	}*/
	
	APlayerCharacter* IPlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (IPlayerCharacter)
	{
		IPlayerCharacter->MoveUp(pValue);
	}
}

void AProtoR4PlayerController::MoveRight(float pValue)
{
	/*if (GEngine && (pValue != 0.f))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("AProtoR4PlayerController::MoveRight"));
	}*/

	APlayerCharacter* IPlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (IPlayerCharacter)
	{
		IPlayerCharacter->MoveRight(pValue);
	}
}

void AProtoR4PlayerController::LeftMouseClick()
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("AProtoR4PlayerController::LeftMouseClick"));
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);		

		APlayerCharacter* IPlayerCharacter = Cast<APlayerCharacter>(GetPawn());

		if (IPlayerCharacter)
		{
			IPlayerCharacter->LeftMouseClick(Hit);
		}
	}
}

void AProtoR4PlayerController::LeftMouseRelease()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("AProtoR4PlayerController::LeftMouseRelease"));
	}*/
}
