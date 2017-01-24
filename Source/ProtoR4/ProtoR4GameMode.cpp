// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProtoR4.h"
#include "ProtoR4GameMode.h"
#include "ProtoR4PlayerController.h"

#include "PlayerHUD.h"
#include "PlayerCharacter.h"

AProtoR4GameMode::AProtoR4GameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = AProtoR4PlayerController::StaticClass();
	HUDClass = APlayerHUD::StaticClass();
		
	static ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintPlayerCharacterClass(TEXT("Blueprint'/Game/Character/BP_Character.BP_Character'"));
	if (BlueprintPlayerCharacterClass.Object != NULL)
	{
		DefaultPawnClass = Cast<UClass>(BlueprintPlayerCharacterClass.Object->GeneratedClass);
	}
}


