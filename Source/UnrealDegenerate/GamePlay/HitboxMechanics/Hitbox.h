// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Box2D.h"
#include "Components/SceneComponent.h"
#include "Hitbox.generated.h"


DECLARE_DELEGATE_OneParam(FIntersectHitbox, UHitbox*);

UENUM()
enum EHitboxType
{
	PROXIMITY, //This will not apply damage, but instead can be used to gather certain information before a hit. May need to look more into this later...
	HITBOX,//Gives damage
	HURTBOX,//Receives Damage. Cannot collide with other hurtboxes
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHittable : public UInterface
{
	GENERATED_BODY()
};


/**
 *
 */
class UNREALDEGENERATE_API IHittable
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* This function will be called whenever a valid hitbox overlap has begun */
	UFUNCTION(Category = "Hitbox")
	virtual void OnHitboxOverlapBegin(UHitbox* OwnedHitbox, UHitbox* OtherHitbox) = 0;

	/* This function will be called whenever a valid hitbox overlap has ended */
	UFUNCTION(Category = "Hitbox")
	virtual void OnHitboxOverlapEnd(UHitbox* OwnedHitbox, UHitbox* OtherHitbox) = 0;
};

UCLASS()
class UNREALDEGENERATE_API UHitbox : public USceneComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UHitbox();

	/* Updates the Hitbox bounds from our actor location and adjusted scale */
	void UpdateHitboxBoundsBasedOnPositionAndScale();

	/* Method to check if our hitbox is intersecting with another hitbox */
	bool IsHitboxIntersecting(UHitbox* OtherHitbox);

	/* Checks to see if this hitbox should trigger a begin overlap event */
	bool IsBeginOverlap(UHitbox* OtherHitbox);

	/* Checks to see if this hitbox should generate an end overlap event*/
	bool IsEndOverlap(UHitbox* OtherHitbox);

	void AddHitboxToOverlapSet(UHitbox* OtherHitbox);

	void RemoveHitboxFromOverlapSet(UHitbox* OtherHitbox);

	void SetHitboxOwner(IHittable* NewHitboxOwner);

	/* Returns the IHittable owner of the hitbox */
	IHittable* GetHitboxOwner() const { return AssignedHittableActor; }

protected:

	UFUNCTION(Category=Debug)
	/* Draws a hitbox so that we can visually see where our hitbox is place in the world */
	void DebugDrawHitbox();

private:
	/* The actor that can be hit */
	IHittable* AssignedHittableActor;

	FIntersectHitbox HitboxIntersect;

private:
	/* 
	* The assigned type of our hitbox 
	* NOTE: this value should only be set once. Can not be reassigned after creation
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EHitboxType> AssignedHitboxType;

	/* The box2d bounds of our collider */
	FBox2D AssociatedBounds;

	/* Set of all the hitboxes that are currently overlapping with this hitbox */
	TSet<UHitbox*> OverlappingHitboxSet;
};



