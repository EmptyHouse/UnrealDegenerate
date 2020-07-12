// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

private:

	const FVector PlaneConstraintVector = FVector(1.f, 0.f, 1.f);
	
};
