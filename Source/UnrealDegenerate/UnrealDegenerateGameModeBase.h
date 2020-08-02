// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay/HitboxMechanics/HitboxManager.h"
#include "Gameplay/DefaultPlayerBindings.h"
#include "UnrealDegenerateGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEGENERATE_API AUnrealDegenerateGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
		FVector GetPlaneConstraintVector() const {
		return PlaneConstraintVector;
	}

	/* Returns an instance of the Hitbox Manager that is being used for this round */
	//UHitboxManager* GetHitboxManager() { return HitboxManager; }

	UPROPERTY(EditDefaultsOnly)
	UDefaultInputProperties* DefaultInputProperties;

private:

	const FVector PlaneConstraintVector = FVector(1.f, 0.f, 1.f);
	//UHitboxManager* HitboxManager = NewObject<UHitboxManager>();
	
};
