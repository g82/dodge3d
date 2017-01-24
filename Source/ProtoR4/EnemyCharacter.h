

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AEnemyCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

		UFUNCTION()
		void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
