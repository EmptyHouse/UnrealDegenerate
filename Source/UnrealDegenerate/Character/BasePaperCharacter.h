// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "BasePaperCharacter.generated.h"

UCLASS()
class UNREALDEGENERATE_API ABasePaperCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePaperCharacter();

protected:

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent* SpriteFlipbook;

	UPROPERTY(EditAnywhere)
	UBaseCharacterMovementComponent* CharacterMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
