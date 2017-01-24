

#include "ProtoR4.h"
#include "EnemyCharacter.h"


AEnemyCharacter::AEnemyCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> IEnemyMesh(TEXT("SkeletalMesh'/Game/Character/IceGiant.IceGiant'"));
	Mesh->SetSkeletalMesh(IEnemyMesh.Object);
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
	Mesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	UCapsuleComponent* capsule = Cast<UCapsuleComponent>(RootComponent);
	capsule->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);
}

void AEnemyCharacter::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	FName name = OtherComp->GetCollisionProfileName();
	if (!name.Compare(FName(TEXT("Projectile"))))
	{
		Destroy();
	}
}
