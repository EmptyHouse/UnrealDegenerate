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

	InputActionKeyDictionary.Add(EInputActions::LightAttack);
	InputActionKeyDictionary.Add(EInputActions::MediumAttack);
	InputActionKeyDictionary.Add(EInputActions::HeavyAttack);
	InputActionKeyDictionary.Add(EInputActions::Special);
	InputActionKeyDictionary.Add(EInputActions::Right);
	InputActionKeyDictionary.Add(EInputActions::Left);
	InputActionKeyDictionary.Add(EInputActions::Up);
	InputActionKeyDictionary.Add(EInputActions::Down);
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

	ClearInputActionDictionary();
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FPlayerInputPacket FrameInputPacket = ConstructInputPacketFromKeyDictionary();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Format for bindings should be BindingName_PlayerIndex. Ex: Horizontal_1 for horizontal player 1)
	const int32 PlayerIndex = UGameplayStatics::GetPlayerControllerID(this) + 1;
	const bool bIsPlayerOne = PlayerIndex == 1;

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

			UDataTable* AxisBindingTable = DefaultAxisDataTable;
			TArray<FName> RowNames = AxisBindingTable->GetRowNames();
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
					const FName InputMappingName = CreatePlayerIndexInputBinding(RowName, PlayerIndex);

					FInputActionKeyMapping ActionKeyMapping;
					ActionKeyMapping.Key = bIsPlayerOne ? InputBinding->PlayerOneActionBindKey : InputBinding->PlayerTwoActionBindKey;
					ActionKeyMapping.ActionName = InputMappingName;
					PlayerInput->ActionMappings.Add(ActionKeyMapping);
				}
			}
		}
	}

	const FName HorizontalName = CreatePlayerIndexInputBinding(HorizontalAxisName, PlayerIndex);
	const FName VerticalName = CreatePlayerIndexInputBinding(VerticalAxisName, PlayerIndex);

	InputComponent->BindAxis(HorizontalName, this, &ABasePlayerController::OnHorizontalAxisChange);
	InputComponent->BindAxis(VerticalName, this, &ABasePlayerController::OnVerticalAxisChange);

	static const FName LightAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::LightAttack).ToString());
	const FName LightAttackName = CreatePlayerIndexInputBinding(LightAttackActionName, PlayerIndex);
	InputComponent->BindAction(LightAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnLightAttackPressed);
	InputComponent->BindAction(LightAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnLightAttackReleased);
}

#pragma region Input Binding Methods

void ABasePlayerController::OnHorizontalAxisChange(float AxisValue)
{
	InputActionKeyDictionary[EInputActions::Right] = AxisValue > 0.f;
	InputActionKeyDictionary[EInputActions::Left] = AxisValue < 0.f;
	if (AxisValue != 0.0f)
	{
		AxisValue = AxisValue;
	}
}

void ABasePlayerController::OnVerticalAxisChange(float AxisValue)
{
	InputActionKeyDictionary[EInputActions::Up] = AxisValue > 0.f;
	InputActionKeyDictionary[EInputActions::Down] = AxisValue < 0.f;
}

void ABasePlayerController::OnLightAttackPressed()
{
	InputActionKeyDictionary[EInputActions::LightAttack] = true;
}

void ABasePlayerController::OnLightAttackReleased()
{
	InputActionKeyDictionary[EInputActions::LightAttack] = false;
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

#pragma endregion Input Binding Methods

bool ABasePlayerController::IsInputKeyPressed(const EInputActions KeyToEvaluate)  const
{
	return InputActionKeyDictionary[KeyToEvaluate];
}

FPlayerInputPacket ABasePlayerController::ConstructInputPacketFromKeyDictionary()
{
	FPlayerInputPacket InputPacket;
	InputPacket.PlayerIndex = UGameplayStatics::GetPlayerControllerID(this) + 1;
	
	uint8 InputPattern = 0x00;
	InputPattern |= (uint8)IsInputKeyPressed(EInputActions::LightAttack);
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::MediumAttack)) << 1;
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::HeavyAttack)) << 2;
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::Special)) << 3;
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::Left)) << 4;
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::Right)) << 5;
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::Up)) << 6;
	InputPattern |= ((uint8)IsInputKeyPressed(EInputActions::Down)) << 7;
	InputPacket.InputPattern = InputPattern;

	return InputPacket;
}

void ABasePlayerController::ClearInputActionDictionary()
{
	InputActionKeyDictionary[EInputActions::LightAttack] = false;
	InputActionKeyDictionary[EInputActions::MediumAttack] = false;
	InputActionKeyDictionary[EInputActions::HeavyAttack] = false;
	InputActionKeyDictionary[EInputActions::Special] = false;
	InputActionKeyDictionary[EInputActions::Right] = false;
	InputActionKeyDictionary[EInputActions::Left] = false;
	InputActionKeyDictionary[EInputActions::Up] = false;
	InputActionKeyDictionary[EInputActions::Down] = false;
}
