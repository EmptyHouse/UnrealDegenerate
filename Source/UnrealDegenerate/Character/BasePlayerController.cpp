// Copyright © 2020 Fucking Degenerate Games Inc.

#include "BasePlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer) {

}

const FName ABasePlayerController::HorizontalAxisName = FName(TEXT("HorizontalMove"));

const FName ABasePlayerController::VerticalAxisName = FName(TEXT("VerticalMove"));

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputActionKeyDictionary.Reset();

	SetupInputComponent();
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const int32 PlayerIndex = UGameplayStatics::GetPlayerControllerID(this);

	//static ConstructorHelpers::FObjectFinder<UDefaultPlayerBindings> DefaultInputBindings = (TEXT("/Game/DA_DefaultPlayerBindings.DA_DefaultPlayerBindings'"));
}

#pragma region Input Binding Methods

void ABasePlayerController::OnHorizontalAxisChange(float AxisValue)
{
}

void ABasePlayerController::OnVerticalAxisChange(float AxisValue)
{
}

void ABasePlayerController::OnLightAttackPressed()
{

}

void ABasePlayerController::OnLightAttackReleased()
{
}

void ABasePlayerController::OnMediumAttackPressed()
{
}

void ABasePlayerController::OnMediumAttackReleased()
{
}

void ABasePlayerController::OnHeavyAttackPressed()
{
}

void ABasePlayerController::OnHeavyAttackReleased()
{
}

void ABasePlayerController::OnSpecialAttackPressed()
{
}

void ABasePlayerController::OnSpecialAttackReleased()
{
}

FPlayerInputPacket ABasePlayerController::ConstructInputPacket() const
{
	return FPlayerInputPacket();
}

#pragma endregion Input Binding Methods
