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
	UE_LOG(LogTemp, Warning, TEXT("%f"), Velocity.X);
	UE_LOG(LogTemp, Warning, TEXT("%f"), UpdatedComponent->ComponentVelocity.X);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *UpdatedComponent->GetFName().ToString());
}
