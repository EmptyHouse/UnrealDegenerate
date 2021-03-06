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


private:
	TMap<IHittable*, TSet<UHitbox*>> HitboxMap;

public:

	/* Should only be constructed in the game manager */
	UHitboxManager();

	/* Add hitbox to our manager. This should be done whenever our hitbox has been spawned into the world */
	void AddHitboxToManager(UHitbox* HitboxToAdd);

	/* Safely remove a hitbox from the manager. This should be done whenever our hitbox has been destroyed. */
	void RemoveHitboxFromManager(UHitbox* HitboxToRemove);

	/* Call this method every frame to check for hitbox intersections that take place in our game */
	void UpdateHitboxManager();

	/* Set whether or not we want to draw our debug hitboxes */
	UFUNCTION(BlueprintCallable, Category = Hitbox)
	void SetShouldDrawDebugHitboxes(bool ShouldDrawDebugHitboxes);

	/* Returns whether or not our hitbox manager is set to draw debug hitboxes */
	UFUNCTION(BlueprintCallable, Category = Hitbox)
	bool GetDrawDebugHitboxesOn() const { return IsDebugDrawHitboxesOn; }

private:
	/* Method to check against all valid hitbox intersections */
	void CheckForAllHitboxIntersections();

	/* This method will handle logic when an hitbox intersects with another hitbox. This will happen the first frame that our hitboxes intersect*/
	void OnHitboxBeginOverlap(UHitbox* Hitbox1, UHitbox* Hitbox2);

	/* This method will handle logic when a hitbox ends its intersection with another hitbox. Happens on the first frame that our hitboxes end their overlap*/
	void OnHitboxEndOverlap(UHitbox* Hitbox1, UHitbox* Hitbox2);

private:
	bool IsDebugDrawHitboxesOn;
};