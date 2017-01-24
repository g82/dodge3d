// Copyright 1998 - 2014 Epic Games, Inc.All Rights Reserved.

#include "ProtoR4.h"
#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> IPlayerMesh(TEXT("SkeletalMesh'/Game/Character/HeroTPP.HeroTPP'"));

	Mesh->SetSkeletalMesh(IPlayerMesh.Object);
	Mesh->SetRelativeLocation(FVector(0, 0, -90), false);
	Mesh->SetRelativeRotation(FRotator(0, -90, 0), false);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CharacterMovement->bOrientRotationToMovement = true;
	CharacterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	CharacterMovement->bConstrainToPlane = true;
	CharacterMovement->bSnapToPlaneAtStart = true;

	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUseControllerViewRotation = false;

	CurrentWeapon = NewObject<UWeapon>(this, UWeapon::StaticClass());
	//CurrentWeapon = PCIP.CreateDefaultSubobject<UWeapon>(this, TEXT("CurrentWeapon"));
	CurrentWeapon->Initialize(this);
	

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> IWeaponMesh(TEXT("SkeletalMesh'/Game/Weapons/Launcher.Launcher'"));
	WeaponMesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMeshComponent"));
	WeaponMesh->AttachTo(RootComponent);
	WeaponMesh->SetSkeletalMesh(IWeaponMesh.Object);
	
}

void APlayerCharacter::BeginPlay()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("APlayerCharacter::BeginPlay()"));
	}
}

void APlayerCharacter::MoveUp(float pValue)
{
	if ((Controller != NULL) && (pValue != 0.0f))
	{
		const FVector Direction = FVector(1.0f, 0.0f, 0.0f);
		AddMovementInput(Direction, pValue);
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("APlayerCharacter::MoveUp()"));
	}
}

void APlayerCharacter::MoveRight(float pValue)
{
	if ((Controller != NULL) && (pValue != 0.0f))
	{
		const FVector Direction = FVector(0.0f, 1.0f, 0.0f);
		AddMovementInput(Direction, pValue);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("APlayerCharacter::MoveRight()"));
	}
}

void APlayerCharacter::LeftMouseClick(FHitResult& Hit)
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("APlayerCharacter::LeftMouseClick"));

	}
	CurrentWeapon->ShootProjectile();
}

FVector APlayerCharacter::GetMuzzleSocketLocation() const
{	
	return WeaponMesh->GetSocketLocation(TEXT("MuzzleFlashSocket"));
}

FRotator APlayerCharacter::GetMuzzleSocketRotation() const
{
	return WeaponMesh->GetSocketRotation(TEXT("MuzzleFlashSocket"));
}
