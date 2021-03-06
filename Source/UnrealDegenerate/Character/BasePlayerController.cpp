// Copyright © 2020 Fucking Degenerate Games Inc.

#include "BasePlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "../Gameplay/DefaultPlayerBindings.h"
#include "../UnrealDegenerateGameModeBase.h"
#include "../Character/BasePaperCharacter.h"
#include "../InputTypes.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer) {

	CurrentInputPattern = 0x00;
}

const FName ABasePlayerController::HorizontalAxisName = FName(TEXT("HorizontalMove"));

const FName ABasePlayerController::VerticalAxisName = FName(TEXT("VerticalMove"));

static FName CreatePlayerIndexInputBinding(const FName& BindingName, int32 PlayerIndex)
{
	// Replace empty spaces in string
	return FName(FString::Printf(TEXT("%s_%s"), *BindingName.ToString().Replace(TEXT(" "), TEXT("")), *FString::FromInt(PlayerIndex)));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	CurrentInputPattern = 0x00;
	PreviousInputPattern = 0x00;
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!InputQueue.IsEmpty())
	{
		FPlayerInputPacket PlayerInputPacket;
		InputQueue.Dequeue(PlayerInputPacket);
		OnPlayerPacketReady.Broadcast(PlayerInputPacket);
	}

	if (PreviousInputPattern != CurrentInputPattern)
	{
		FPlayerInputPacket PacketToQueue(0, PlayerID, CurrentInputPattern);
		InputQueue.Enqueue(PacketToQueue);
	}

	PreviousInputPattern = CurrentInputPattern;
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	PlayerID = UGameplayStatics::GetPlayerControllerID(this) + 1;

	// Format for bindings should be BindingName_PlayerIndex. Ex: Horizontal_1 for horizontal player 1)
	const bool bIsPlayerOne = PlayerID == 1;

	AUnrealDegenerateGameModeBase* GameMode = Cast<AUnrealDegenerateGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	// TODO: Replace with loading from persisted player settings.
	// Ideally, this will be set from a sort of menu
	if (GameMode && GameMode->DefaultInputProperties)
	{
		UDataTable* DefaultAxisDataTable = GameMode->DefaultInputProperties->DefaultInputAxisBindings;

		// Create axis bindings
		if (DefaultAxisDataTable)
		{
			PlayerInput->AxisMappings.Empty();

			TArray<FName> RowNames = DefaultAxisDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FPlayerAxisBinding* AxisBinding = DefaultAxisDataTable->FindRow<FPlayerAxisBinding>(RowName, TEXT(""));
				if (AxisBinding)
				{
					FName AxisMappingName = CreatePlayerIndexInputBinding(RowName, PlayerID);

					FInputAxisKeyMapping AxisMappingPositive(AxisMappingName, bIsPlayerOne ? AxisBinding->PlayerOnePositiveAxisBindingKey : AxisBinding->PlayerTwoPositiveAxisBindingKey, 1.0f);
					PlayerInput->AxisMappings.Add(AxisMappingPositive);

					FInputAxisKeyMapping AxisMappingNegative(AxisMappingName, bIsPlayerOne ? AxisBinding->PlayerOneNegativeAxisBindingKey : AxisBinding->PlayerTwoNegativeAxisBindingKey, -1.0f);
					PlayerInput->AxisMappings.Add(AxisMappingNegative);
				}
			}
		}

		//Create input bindings
		UDataTable* DefaultInputDataTable = GameMode->DefaultInputProperties->DefaultInputActionBindings;
		if (DefaultInputDataTable)
		{
			PlayerInput->ActionMappings.Empty();

			TArray<FName> RowNames = DefaultInputDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FPlayerInputBinding* InputBinding = DefaultInputDataTable->FindRow<FPlayerInputBinding>(RowName, TEXT(""));
				if (InputBinding)
				{
					const FName InputMappingName = CreatePlayerIndexInputBinding(RowName, PlayerID);

					FInputActionKeyMapping ActionKeyMapping(InputMappingName, bIsPlayerOne ? InputBinding->PlayerOneActionBindKey : InputBinding->PlayerTwoActionBindKey);
					PlayerInput->ActionMappings.Add(ActionKeyMapping);
				}
			}
		}
	}

	const FName HorizontalName = CreatePlayerIndexInputBinding(HorizontalAxisName, PlayerID);
	const FName VerticalName = CreatePlayerIndexInputBinding(VerticalAxisName, PlayerID);

	InputComponent->BindAxis(VerticalName, this, &ABasePlayerController::OnVerticalAxisChange);
	InputComponent->BindAxis(HorizontalName, this, &ABasePlayerController::OnHorizontalAxisChange);

	static const FName LightAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::LightAttack).ToString());
	const FName LightAttackName = CreatePlayerIndexInputBinding(LightAttackActionName, PlayerID);
	InputComponent->BindAction(LightAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnLightAttackPressed);
	InputComponent->BindAction(LightAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnLightAttackReleased);

	static const FName MediumAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::MediumAttack).ToString());
	const FName MediumAttackName = CreatePlayerIndexInputBinding(MediumAttackActionName, PlayerID);
	InputComponent->BindAction(MediumAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnMediumAttackPressed);
	InputComponent->BindAction(MediumAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnMediumAttackReleased);

	static const FName HeavyAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::HeavyAttack).ToString());
	const FName HeavyAttackName = CreatePlayerIndexInputBinding(HeavyAttackActionName, PlayerID);
	InputComponent->BindAction(HeavyAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnHeavyAttackPressed);
	InputComponent->BindAction(HeavyAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnHeavyAttackReleased);

	static const FName SpecialAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::Special).ToString());
	const FName SpecialAttackName = CreatePlayerIndexInputBinding(SpecialAttackActionName, PlayerID);
	InputComponent->BindAction(SpecialAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnSpecialAttackPressed);
	InputComponent->BindAction(SpecialAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnSpecialAttackReleased);
}

#pragma region Input Binding Methods

void ABasePlayerController::OnHorizontalAxisChange(float AxisValue)
{
	if (AxisValue < 0.f)
	{
		CurrentInputPattern |= (uint8)EInputActions::Left;
		CurrentInputPattern &= ~(uint8)EInputActions::Right;
	}
	else if (AxisValue > 0.f)
	{
		CurrentInputPattern &= ~(uint8)(EInputActions::Left);
		CurrentInputPattern |= (uint8)(EInputActions::Right);
	}
	else
	{
		CurrentInputPattern &= ~((uint8)EInputActions::Left | (uint8)EInputActions::Right);
	}
}

void ABasePlayerController::OnVerticalAxisChange(float AxisValue)
{
	if (AxisValue > 0.0f)
	{
		CurrentInputPattern |= (uint8)EInputActions::Up;
		CurrentInputPattern &= ~(uint8)EInputActions::Down;
	}
	else if (AxisValue < 0.0f)
	{
		CurrentInputPattern &= ~(uint8)EInputActions::Up;
		CurrentInputPattern |= (uint8)EInputActions::Down;
	}
	else
	{
		CurrentInputPattern &= ~((uint8)EInputActions::Up | (uint8)EInputActions::Down);
	}
}

void ABasePlayerController::OnLightAttackPressed()
{
	CurrentInputPattern |= (uint8)EInputActions::LightAttack;
}

void ABasePlayerController::OnLightAttackReleased()
{
	CurrentInputPattern &= ~(uint8)EInputActions::LightAttack;
}

void ABasePlayerController::OnMediumAttackPressed()
{
	CurrentInputPattern |= (uint8)EInputActions::MediumAttack;
}

void ABasePlayerController::OnMediumAttackReleased()
{
	CurrentInputPattern &= ~(uint8)EInputActions::MediumAttack;
}

void ABasePlayerController::OnHeavyAttackPressed()
{
	CurrentInputPattern |= (uint8)EInputActions::HeavyAttack;
}

void ABasePlayerController::OnHeavyAttackReleased()
{
	CurrentInputPattern &= ~(uint8)EInputActions::HeavyAttack;
}

void ABasePlayerController::OnSpecialAttackPressed()
{
	CurrentInputPattern |= (uint8)EInputActions::Special;
}

void ABasePlayerController::OnSpecialAttackReleased()
{
	CurrentInputPattern &= ~(uint8)EInputActions::Special;
}

#pragma endregion Input Binding Methods
