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
 * This is the interface for actors that can receive or give hits
 */
class UNREALDEGENERATE_API IHittable
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* This function will be called whenever a valid hitbox overlap has begun */
	UFUNCTION(BlueprintImplementableEvent, Category = Hitbox)
	void OnHitboxOverlapBegin(UHitbox* OwnedHitbox, UHitbox* OtherHitbox);

	/* This function will be called whenever a valid hitbox overlap has ended */
	UFUNCTION(BlueprintImplementableEvent, Category = Hitbox)
	void OnHitboxOverlapEnd(UHitbox* OwnedHitbox, UHitbox* OtherHitbox);
};


UCLASS()
class UNREALDEGENERATE_API UHitbox : public USceneComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UHitbox();

	virtual void BeginPlay() override;

	/* Updates the Hitbox bounds from our actor location and adjusted scale */
	void UpdateHitboxBoundsBasedOnPositionAndScale();

	/* Method to check if our hitbox is intersecting with another hitbox */
	bool IsHitboxIntersecting(UHitbox* OtherHitbox);

	/* Checks to see if this hitbox should trigger a begin overlap event */
	bool IsBeginOverlap(UHitbox* OtherHitbox);

	/* Checks to see if this hitbox should generate an end overlap event */
	bool IsEndOverlap(UHitbox* OtherHitbox);

	/* This method will be called when we begin overlap with another hitbox */
	void BeginHitboxOverlap(UHitbox* OtherHitbox);

	/* This method will be called when we end overlap with another hitbox */
	void EndHitboxOverlap(UHitbox* OtherHitbox);

	/* Safely adds a hitbox to our hitbox overlap set */
	void AddHitboxToOverlapSet(UHitbox* OtherHitbox);

	/* Safely removes a hitbox from our overlap hitbox set*/
	void RemoveHitboxFromOverlapSet(UHitbox* OtherHitbox);

	/* Set this hitbox owner */
	void SetHitboxOwner(IHittable* NewHitboxOwner);

	/* Returns the IHittable owner of the hitbox */
	IHittable* GetHitboxOwner() const { return HitboxOwner; }

private:
	/* The actor that can be hit */
	IHittable* HitboxOwner;

	/*  */
	FIntersectHitbox HitboxIntersect;

private:
	/* 
	* The assigned type of our hitbox 
	* NOTE: this value should only be set once. Can not be reassigned after creation
	*/
	UPROPERTY(EditDefaultsOnly, Category = Hitbox, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EHitboxType> AssignedHitboxType;

	/* The box2d bounds of our collider */
	FBox2D AssociatedBounds;

	/* Set of all the hitboxes that are currently overlapping with this hitbox */
	TSet<UHitbox*> OverlappingHitboxSet;


	/**************** Debug Functions **************/
public:
	UFUNCTION(BlueprintCallable, Category = Debug)
	/* Sets whether or not we should draw our hitboxes in the scene. Good for debugging. Possibly might be good for a practice mode in the future*/
	void SetDebugDraw(bool ShouldDrawDebugHitbox);

protected:
	UFUNCTION(Category = Debug)
	/* Draws a hitbox so that we can visually see where our hitbox is place in the world */
	void DebugDrawHitbox();

};



