// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "BaseCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEGENERATE_API UBaseCharacterMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:

	UBaseCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);
	
};
