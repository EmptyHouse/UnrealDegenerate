// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "BasePlayerController.h"

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

	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->OnPlayerPacketReady.AddDynamic(this, &ABasePaperCharacter::ProcessPlayerInputPacket);
	}
}

void ABasePaperCharacter::ProcessPlayerInputPacket(const FPlayerInputPacket& InputPacketToExecute)
{
	UE_LOG(LogTemp,Warning,TEXT("Pattern: %d"), InputPacketToExecute.InputPattern)
}

// Called every frame
void ABasePaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

