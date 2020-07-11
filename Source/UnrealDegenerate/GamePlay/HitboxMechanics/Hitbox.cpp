// Fill out your copyright notice in the Description page of Project Settings.


#include "Hitbox.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AHitbox::AHitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


/* Update the bounds of our hitbox */
void AHitbox::UpdateHitboxBoundsBasedOnPositionAndScale()
{

}

// Check if we intersect with another hitbox actor
bool AHitbox::IsHitboxIntersecting(AHitbox* OtherHitbox)
{
	return AssociatedBounds.Intersect(OtherHitbox->AssociatedBounds);
}

// 
void AHitbox::RemoveHitboxesThatAreNoLongerOverlapping()
{
	
}


////////////////Debug Functions//////////////////////////////////////////////

// Draw our hitbox in the world
void AHitbox::DebugDrawHitbox()
{

}
///////////////////////////////////////////////////////////////////////////////
