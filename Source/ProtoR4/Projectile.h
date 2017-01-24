// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	TSubobjectPtr<USphereComponent> ProjectileCollsion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TSubobjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubobjectPtr<UStaticMeshComponent> ProjectileMesh;
		
public:
	
	void InitVelocity(const FVector& ShootDirection);
};