// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ProtoR4.h"
#include "PlayerHUD.h"


APlayerHUD::APlayerHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void APlayerHUD::PostRender()
{
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerOwner->Player);
	FVector2D MousePos = LocalPlayer->ViewportClient->GetMousePosition();
		
	FString TraceLocDebug = TEXT("[HitXYZ]");
	FString TraceActorDebug = TEXT("[HitActor]");
	FString TraceMouseDebug = TEXT("[MouseXY]");

	FVector WorldOrigin, WorldDirection, TraceEnd;
	FHitResult TraceHitResult;
	FCollisionObjectQueryParams TraceObjectParam;
	FCollisionQueryParams TraceParam;

	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	TraceObjectParam.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	TraceParam.bTraceComplex = true;
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;

	if (Canvas != NULL && PlayerOwner != NULL)
	{
		//get 3d from 2d
		Canvas->Deproject(MousePos, WorldOrigin, WorldDirection);

		//calculate trace end vector
		TraceEnd = WorldOrigin + WorldDirection * 65536.0f;

		//trace
		GetWorld()->LineTraceSingle(TraceHitResult, WorldOrigin, TraceEnd, TraceParam, TraceObjectParam);
		MouseWorldPosition = TraceHitResult.ImpactPoint;
		
		TraceLocDebug = TraceLocDebug.operator+(FString::FromInt(int(MouseWorldPosition.X)));
		TraceLocDebug = TraceLocDebug.operator+(" ");
		TraceLocDebug = TraceLocDebug.operator+(FString::FromInt(int(MouseWorldPosition.Y)));
		TraceLocDebug = TraceLocDebug.operator+(" ");
		TraceLocDebug = TraceLocDebug.operator+(FString::FromInt(int(MouseWorldPosition.Z)));
		TraceLocDebug = TraceLocDebug.operator+(" ");
		
		if (TraceHitResult.GetActor() != NULL)
		{
			TraceActorDebug = TraceActorDebug.operator+(TraceHitResult.GetActor()->GetName());
		}

		TraceMouseDebug = TraceMouseDebug.operator+(FString::FromInt(int(MousePos.X)));
		TraceMouseDebug = TraceMouseDebug.operator+(" ");
		TraceMouseDebug = TraceMouseDebug.operator+(FString::FromInt(int(MousePos.Y)));

		UFont* SampleFont = GEngine->GetLargeFont();
		
		float XL, YL;
		FVector2D Pos;

		Canvas->StrLen(SampleFont, TraceActorDebug, XL, YL);
		Pos.X = Canvas->SizeX / 4;
		Pos.Y = Canvas->SizeY / 2;
						
		Canvas->SetDrawColor(FColor(255, 83, 10, 255));
		Canvas->DrawText(SampleFont, TraceActorDebug, Pos.X, Pos.Y, 2.0f, 2.0f);
		Canvas->DrawText(SampleFont, TraceLocDebug, Pos.X, Pos.Y += (2*YL), 2.0f, 2.0f);
		Canvas->DrawText(SampleFont, TraceMouseDebug, Pos.X, Pos.Y += (2*YL), 2.0f, 2.0f);
	}
	else if (Canvas == NULL || PlayerOwner == NULL)
	{
		
	}
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();		
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("APlayerHUD::BeginPlay()"));
	}
}

