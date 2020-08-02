// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Box2D.h"
#include "GameFramework/Actor.h"
#include "Hitbox.generated.h"


DECLARE_DELEGATE_OneParam(FIntersectHitbox, AHitbox*);

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
	virtual void OnHitboxOverlapBegin(AHitbox* OwnedHitbox, AHitbox* OtherHitbox) = 0;

	/* This function will be called whenever a valid hitbox overlap has ended */
	UFUNCTION(Category = "Hitbox")
	virtual void OnHitboxOverlapEnd(AHitbox* OwnedHitbox, AHitbox* OtherHitbox) = 0;
};




UCLASS()
class UNREALDEGENERATE_API AHitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitbox();

	virtual void Tick(float DeltaSeconds) override;

	/* Updates the Hitbox bounds from our actor location and adjusted scale */
	void UpdateHitboxBoundsBasedOnPositionAndScale();

	/* Method to check if our hitbox is intersecting with another hitbox */
	bool IsHitboxIntersecting(AHitbox* OtherHitbox);

	/* Checks to see if this hitbox should trigger a begin overlap event */
	bool IsBeginOverlap(AHitbox* OtherHitbox);

	/* Checks to see if this hitbox should generate an end overlap event*/
	bool IsEndOverlap(AHitbox* OtherHitbox);

	void AddHitboxToOverlapSet(AHitbox* OtherHitbox);

	void RemoveHitboxFromOverlapSet(AHitbox* OtherHitbox);

protected:

	void BeginPlay();

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

	TSet<AHitbox*> OverlappingHitboxSet;
};

