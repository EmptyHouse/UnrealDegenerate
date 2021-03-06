// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Spawnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALDEGENERATE_API ISpawnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(Category = "Spawning")
	virtual void OnSpawn();

	UFUNCTION(Category = "Spawning")
	virtual void OnDespawn();
};
