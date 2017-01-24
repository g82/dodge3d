// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Character.h"
#include "Weapon.h"

#include "PlayerCharacter.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class APlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() OVERRIDE;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TSubobjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TSubobjectPtr<USpringArmComponent> CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubobjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubobjectPtr<UWeapon> CurrentWeapon;*/

public:

	UWeapon* CurrentWeapon;

	void MoveUp(float pValue);
	void MoveRight(float pValue);
	void LeftMouseClick(FHitResult& Hit);

	FVector GetMuzzleSocketLocation() const;
	FRotator GetMuzzleSocketRotation() const;

private:

};
