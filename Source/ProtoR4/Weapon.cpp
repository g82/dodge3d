// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProtoR4.h"
#include "Weapon.h"
#include "PlayerCharacter.h"


UWeapon::UWeapon(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	
}

void UWeapon::Initialize(APawn* pOwnerPawn)
{
	mOwnerPawn = pOwnerPawn;
}

void UWeapon::UpdateWeapon(float pDelta)
{

}

void UWeapon::ShootProjectile()
{
	APlayerCharacter* IPlayer = Cast<APlayerCharacter>(mOwnerPawn);
	
	if (IPlayer)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("UWeapon::ShootProjectile()"));
		}
		
		FVector const MuzzleLocation = IPlayer->GetMuzzleSocketLocation();
		FRotator const MuzzleRotation = IPlayer->GetActorForwardVector().Rotation();
				
		AProjectile* const IProjectile = GWorld->SpawnActor<AProjectile>(MuzzleLocation, MuzzleRotation);

		FVector LaunchDir = IPlayer->GetActorForwardVector();
		LaunchDir.Normalize();

		if (IProjectile)
		{			
			IProjectile->InitVelocity(LaunchDir);
		}

	}
}

bool UWeapon::StartFire()
{
	return false;
}

bool UWeapon::StopFire()
{
	return false;
}

EWeaponState::State UWeapon::GetCurrentState() const
{
	return mCurrentState;
}



