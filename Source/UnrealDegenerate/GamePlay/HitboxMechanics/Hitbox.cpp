// Fill out your copyright notice in the Description page of Project Settings.


#include "Hitbox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
 

// Sets default values
AHitbox::AHitbox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set default values here
	AssignedHitboxType = EHitboxType::HITBOX;//Default will be assigned on start, but can also be assigned when spawned
}


void AHitbox::BeginPlay()
{

}

//NOTE: This may need to be removed later in development but currently I am using it as a debug update
void AHitbox::Tick(float DeltaSeconds)
{
	UpdateHitboxBoundsBasedOnPositionAndScale();
	DebugDrawHitbox();
}


/* Update the bounds of our hitbox */
void AHitbox::UpdateHitboxBoundsBasedOnPositionAndScale()
{
	FVector Position = GetActorLocation();
	FVector HalfScale = (GetActorScale()) / 2.f;

	AssociatedBounds.Min = FVector2D(Position.X - HalfScale.X, Position.Z - HalfScale.Z);
	AssociatedBounds.Max = FVector2D(Position.X + HalfScale.X, Position.Z + HalfScale.Z);
}

// Check if we intersect with another hitbox actor
bool AHitbox::IsHitboxIntersecting(AHitbox* OtherHitbox)
{
	return AssociatedBounds.Intersect(OtherHitbox->AssociatedBounds);
}

// Remove hitboxes if they are no longer valid
void AHitbox::RemoveHitboxesThatAreNoLongerOverlapping()
{
	
}

#pragma region Debug Methods
// Draw our hitbox in the world
void AHitbox::DebugDrawHitbox()
{
	FVector ActorLocation = GetActorLocation();
	FVector BR = FVector(AssociatedBounds.Max.X, ActorLocation.Y, AssociatedBounds.Min.Y);//Bottom Right
	FVector BL = FVector(AssociatedBounds.Min.X, ActorLocation.Y, AssociatedBounds.Min.Y);//Bottom Left
	FVector TR = FVector(AssociatedBounds.Max.X, ActorLocation.Y, AssociatedBounds.Max.Y);//Top Right
	FVector TL = FVector(AssociatedBounds.Min.X, ActorLocation.Y, AssociatedBounds.Max.Y);//Top Left

	FColor DebugColor;


	switch (AssignedHitboxType)
	{
	case EHitboxType::HITBOX:
		DebugColor = FColor(200, 20, 20);
		break;
	case EHitboxType::HURTBOX:
		DebugColor = FColor(0, 128, 128);
		break;
	default:
		DebugColor = FColor(255, 255, 255);//White if the assigned type is invalid
		break;
	}

	DrawDebugLine(GetWorld(), BR, BL, DebugColor, false, 0, 0, 1.f);
	DrawDebugLine(GetWorld(), BL, TL, DebugColor, false, 0, 0, 1.f);
	DrawDebugLine(GetWorld(), TL, TR, DebugColor, false, 0, 0, 1.f);
	DrawDebugLine(GetWorld(), TR, BR, DebugColor, false, 0, 0, 1.f);

}
#pragma endregion Debug Methods
