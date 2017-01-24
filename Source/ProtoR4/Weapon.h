// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Object.h"
#include "Projectile.h"
#include "Weapon.generated.h"

/**
 * 
 */
namespace EWeaponState
{
	enum State
	{
		IDLE,
		FIRING,
	};
}

UCLASS()
class UWeapon : public UObject
{
	GENERATED_UCLASS_BODY()

	void Initialize(APawn* pOwnerPawn);
	void UpdateWeapon(float pDelta);
	void ShootProjectile();
	bool StartFire();
	bool StopFire();
	EWeaponState::State GetCurrentState() const;
	
protected:

	EWeaponState::State mCurrentState;

	UPROPERTY()
	APawn* mOwnerPawn;
	float mFireSensitive;
	float mFireInterval;
	float mNextFire;
		
};
