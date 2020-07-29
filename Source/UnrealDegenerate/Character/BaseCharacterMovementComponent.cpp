// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterMovementComponent.h"

UBaseCharacterMovementComponent::UBaseCharacterMovementComponent(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UBaseCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateComponentVelocity();
	UpdatePosition(DeltaTime);
}

void UBaseCharacterMovementComponent::UpdatePosition(float DeltaTime)
{
	FVector VelocityToUse = Velocity;
	const FVector CurrentPosition = UpdatedComponent->GetComponentLocation();
	FVector Target = CurrentPosition + (Velocity * DeltaTime);
	FQuat fuck;
	//UpdatedComponent->MoveComponent(Target, fuck, false);
	ConsumeInputVector();
}
