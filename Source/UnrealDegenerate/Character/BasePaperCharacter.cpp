// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"

// Sets default values
ABasePaperCharacter::ABasePaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxCollider);

	SpriteFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpriteFlipbook->SetupAttachment(BoxCollider);

	CharacterMovementComponent = CreateDefaultSubobject<UBaseCharacterMovementComponent>(TEXT("Movement Component"));
	CharacterMovementComponent->SetPlaneConstraintNormal(FVector(1.f, 0.f, 1.f));
	CharacterMovementComponent->SetPlaneConstraintEnabled(true);
}

// Called when the game starts or when spawned
void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

// Called every frame
void ABasePaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

