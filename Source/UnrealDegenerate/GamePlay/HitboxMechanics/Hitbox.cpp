// Fill out your copyright notice in the Description page of Project Settings.


#include "Hitbox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
 

// Sets default values
UHitbox::UHitbox()
{
	//Set default values here
	AssignedHitboxType = EHitboxType::HITBOX;//Default will be assigned on start, but can also be assigned when spawned
}

void UHitbox::BeginPlay()
{
	if (IHittable* HittableParent = Cast<IHittable>(GetOwner()))
	{
		SetHitboxOwner(HittableParent);
	}
}

void UHitbox::UpdateHitboxBoundsBasedOnPositionAndScale()
{
	FVector Position = GetOwner()->GetActorLocation();
	FVector HalfScale = (GetOwner()->GetActorScale()) / 2.f;

	AssociatedBounds.Min = FVector2D(Position.X - HalfScale.X, Position.Z - HalfScale.Z);
	AssociatedBounds.Max = FVector2D(Position.X + HalfScale.X, Position.Z + HalfScale.Z);
}

bool UHitbox::IsHitboxIntersecting(UHitbox* OtherHitbox)
{
	return AssociatedBounds.Intersect(OtherHitbox->AssociatedBounds);
}

bool UHitbox::IsBeginOverlap(UHitbox* Otherhitbox)
{
	return !OverlappingHitboxSet.Contains(Otherhitbox);
}

bool UHitbox::IsEndOverlap(UHitbox* OtherHitbox)
{
	return OverlappingHitboxSet.Contains(OtherHitbox);
}

void UHitbox::BeginHitboxOverlap(UHitbox* OtherHitbox)
{
	AddHitboxToOverlapSet(OtherHitbox);
	HitboxOwner->OnHitboxOverlapBegin(this, OtherHitbox);
}

void UHitbox::EndHitboxOverlap(UHitbox* OtherHitbox)
{
	RemoveHitboxFromOverlapSet(OtherHitbox);
	HitboxOwner->OnHitboxOverlapEnd(this, OtherHitbox);
}

void UHitbox::AddHitboxToOverlapSet(UHitbox* OtherHitbox)
{
	if (OverlappingHitboxSet.Contains(OtherHitbox))
	{
		OverlappingHitboxSet.Add(OtherHitbox);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You are trying to add a hitbox that is already present"))
	}
}

void UHitbox::RemoveHitboxFromOverlapSet(UHitbox* OtherHitbox)
{
	if (OverlappingHitboxSet.Contains(OtherHitbox))
	{
		OverlappingHitboxSet.Remove(OtherHitbox);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You are trying to remove a hitbox that was not found."));
	}
}

void UHitbox::SetHitboxOwner(IHittable* NewHitboxOwner)
{
	HitboxOwner = NewHitboxOwner;
}

#pragma region Debug Methods
// Draw our hitbox in the world
void UHitbox::DebugDrawHitbox()
{
	FVector ActorLocation = GetOwner()->GetActorLocation();
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

void UHitbox::SetDebugDraw(bool ShouldDrawHitbox)
{
	
}
#pragma endregion Debug Methods
