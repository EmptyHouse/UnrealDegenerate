// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Box2D.h"
#include "GameFramework/Actor.h"
#include "Hitbox.generated.h"

UENUM()
enum EHitboxType
{
	Hitbox,//We give damage
	Hurtbox,//We receive damage
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

	bool IsHitboxIntersecting(AHitbox* OtherHitbox);

protected:
	/* Draws a hitbox so that we can visually see where our hitbox is place in the world*/
	void DebugDrawHitbox();

private:
	void RemoveHitboxesThatAreNoLongerOverlapping();

public:
	/* The assigned type of our hitbox */
	UPROPERTY(EditDefaultsOnly, Category = "Hitbox")
	TEnumAsByte<EHitboxType> AssignedHitboxType;

private:
	/* The box2d bounds of our collider */
	FBox2D AssociatedBounds;
};
