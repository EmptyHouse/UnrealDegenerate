// Copyright © 2020 Fucking Degenerate Games Inc.


#include "HitboxManager.h"

#pragma region Hitbox Manager
/* Initialize values */
UHitboxManager::UHitboxManager()
{

}

//Safely add a htibox to be managed
void UHitboxManager::AddHitboxToManager(UHitbox* HitboxToAdd)
{
	check(HitboxToAdd->GetHitboxOwner());

	if (!HitboxMap.Contains(HitboxToAdd->GetHitboxOwner()))
	{
		HitboxMap.Add(HitboxToAdd->GetHitboxOwner());
	}
	HitboxMap[HitboxToAdd->GetHitboxOwner()].Add(HitboxToAdd);
}

// Safely remove a hitbox that is no longer being managed
void UHitboxManager::RemoveHitboxFromManager(UHitbox* HitboxToRemove)
{
	check(HitboxToRemove->GetHitboxOwner());

	if (HitboxMap.Contains(HitboxToRemove->GetHitboxOwner()))
	{
		HitboxMap[HitboxToRemove->GetHitboxOwner()].Remove(HitboxToRemove);
		if (HitboxMap[HitboxToRemove->GetHitboxOwner()].Num() == 0)
		{
			HitboxMap.Remove(HitboxToRemove->GetHitboxOwner());
		}
	}
}

void UHitboxManager::UpdateHitboxManager()
{
	CheckForAllHitboxIntersections();
}

void UHitboxManager::CheckForAllHitboxIntersections()
{

}

void UHitboxManager::OnHitboxBeginOverlap(UHitbox* Hitbox1, UHitbox* Hitbox2)
{

}

void UHitboxManager::OnHitboxEndOverlap(UHitbox* Hitbox1, UHitbox* Hitbox2)
{

}
#pragma endregion Hitbox Manager

