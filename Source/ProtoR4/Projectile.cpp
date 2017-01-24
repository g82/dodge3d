// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProtoR4.h"
#include "Projectile.h"

#include "EnemyCharacter.h"


AProjectile::AProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	ProjectileCollsion = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProjectileCollision"));
	ProjectileCollsion->InitSphereRadius(5.0f);	
	RootComponent = ProjectileCollsion;	
	ProjectileCollsion->SetCollisionProfileName("Projectile");
	ProjectileCollsion->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	ProjectileCollsion->bGenerateOverlapEvents = false;
			
	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(ProjectileCollsion);
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> IProjectileMesh(TEXT("StaticMesh'/Game/Shapes/Shape_Sphere.Shape_Sphere'"));
	ProjectileMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("ProjectileMesh"));
	ProjectileMesh->AttachTo(RootComponent);
	ProjectileMesh->SetStaticMesh(IProjectileMesh.Object);
	ProjectileMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));	
	ProjectileMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -5.0f));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->bGenerateOverlapEvents = false;
	
	InitialLifeSpan = 5.0f;
		
}

void AProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("AProjectile::InitVelocity()"));
		}		
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);

		UClass* ActorClass = OtherActor->GetActorClass();

		AEnemyCharacter* enemyClass = Cast<AEnemyCharacter>(ActorClass);

		if (enemyClass)
		{
			OtherActor->Destroy();
		}
		
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("AProjectile::OnHit()"));
		}

		Destroy();
	}

}