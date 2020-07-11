// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"

// Sets default values
ABasePaperCharacter::ABasePaperCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxCollider);

	SpriteFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, false);
	SpriteFlipbook->AttachToComponent(BoxCollider, AttachmentRules);
}

// Called when the game starts or when spawned
void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

