// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Hitbox.h"
#include "HitboxManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEGENERATE_API UHitboxManager : public UObject
{
	GENERATED_BODY()


public:

	/* Should only be constructed in the game manager */
	UHitboxManager();

	/* Add hitbox to our manager. This should be done whenever our hitbox has been spawned into the world */
	void AddHitboxToManager(UHitbox* HitboxToAdd);

	/* Safely remove a hitbox from the manager. This should be done whenever our hitbox has been destroyed. */
	void RemoveHitboxFromManager(UHitbox* HitboxToRemove);

protected:

private:

};