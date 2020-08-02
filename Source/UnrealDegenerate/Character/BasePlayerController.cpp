// Copyright © 2020 Fucking Degenerate Games Inc.

#include "BasePlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "../Gameplay/DefaultPlayerBindings.h"
#include "../UnrealDegenerateGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer) {
}

const FName ABasePlayerController::HorizontalAxisName = FName(TEXT("HorizontalMove"));

const FName ABasePlayerController::VerticalAxisName = FName(TEXT("VerticalMove"));

static FName CreatePlayerIndexInputBinding(const FName& BindingName, int32 PlayerIndex)
{
	return FName(FString::Printf(TEXT("%s_%s"), *BindingName.ToString(), *FString::FromInt(PlayerIndex)));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputActionKeyDictionary.Reset();

	//SetupInputComponent();
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Format for bindings should be BindingName_PlayerIndex. Ex: Horizontal_1 for horizontal player 1)
	const int32 PlayerIndex = UGameplayStatics::GetPlayerControllerID(this) + 1;
	const bool bIsPlayerOne = PlayerIndex == 1;

	AUnrealDegenerateGameModeBase* GameMode = Cast<AUnrealDegenerateGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));


	if (GameMode && GameMode->DefaultInputProperties)
	{
		UDataTable* DefaultAxisDataTable = GameMode->DefaultInputProperties->DefaultInputAxisBindings;

		// Create axis bindings
		if (DefaultAxisDataTable)
		{
			UDataTable* AxisBindingTable = DefaultAxisDataTable;
			TArray<FName> RowNames = AxisBindingTable->GetRowNames();

			PlayerInput->AxisMappings.Empty();

			for (const FName& RowName : RowNames)
			{
				FPlayerAxisBinding* AxisBinding = AxisBindingTable->FindRow<FPlayerAxisBinding>(RowName, TEXT(""));
				if (AxisBinding)
				{
					FName AxisMappingName = CreatePlayerIndexInputBinding(RowName, PlayerIndex);

					FInputAxisKeyMapping AxisMappingPositive;
					AxisMappingPositive.AxisName = AxisMappingName;
					AxisMappingPositive.Key = bIsPlayerOne ? AxisBinding->PlayerOnePositiveAxisBindingKey : AxisBinding->PlayerTwoPositiveAxisBindingKey;
					AxisMappingPositive.Scale = 1.0f;
					PlayerInput->AxisMappings.Add(AxisMappingPositive);

					FInputAxisKeyMapping AxisMappingNegative;
					AxisMappingNegative.AxisName = AxisMappingName;
					AxisMappingNegative.Key = bIsPlayerOne ? AxisBinding->PlayerOneNegativeAxisBindingKey : AxisBinding->PlayerTwoNegativeAxisBindingKey;
					AxisMappingNegative.Scale = -1.0f;
					PlayerInput->AxisMappings.Add(AxisMappingNegative);
				}
			}
		}
	}
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
