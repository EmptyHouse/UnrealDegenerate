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
	// Replace empty spaces in string
	return FName(FString::Printf(TEXT("%s_%s"), *BindingName.ToString().Replace(TEXT(" "), TEXT("")), *FString::FromInt(PlayerIndex)));
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

			TArray<FName> RowNames = DefaultAxisDataTable->GetRowNames();
			for (const FName& RowName : RowNames)
			{
				FPlayerAxisBinding* AxisBinding = DefaultAxisDataTable->FindRow<FPlayerAxisBinding>(RowName, TEXT(""));
				if (AxisBinding)
				{
					FName AxisMappingName = CreatePlayerIndexInputBinding(RowName, PlayerIndex);

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
					const FName InputMappingName = CreatePlayerIndexInputBinding(RowName, PlayerIndex);

					FInputActionKeyMapping ActionKeyMapping(InputMappingName, bIsPlayerOne ? InputBinding->PlayerOneActionBindKey : InputBinding->PlayerTwoActionBindKey);
					PlayerInput->ActionMappings.Add(ActionKeyMapping);
				}
			}
		}
	}

	const FName HorizontalName = CreatePlayerIndexInputBinding(HorizontalAxisName, PlayerIndex);
	const FName VerticalName = CreatePlayerIndexInputBinding(VerticalAxisName, PlayerIndex);

	InputComponent->BindAxis(VerticalName, this, &ABasePlayerController::OnVerticalAxisChange);
	InputComponent->BindAxis(HorizontalName, this, &ABasePlayerController::OnHorizontalAxisChange);

	static const FName LightAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::LightAttack).ToString());
	const FName LightAttackName = CreatePlayerIndexInputBinding(LightAttackActionName, PlayerIndex);
	InputComponent->BindAction(LightAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnLightAttackPressed);
	InputComponent->BindAction(LightAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnLightAttackReleased);

	static const FName MediumAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::MediumAttack).ToString());
	const FName MediumAttackName = CreatePlayerIndexInputBinding(MediumAttackActionName, PlayerIndex);
	InputComponent->BindAction(MediumAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnMediumAttackPressed);
	InputComponent->BindAction(MediumAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnMediumAttackReleased);

	static const FName HeavyAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::HeavyAttack).ToString());
	const FName HeavyAttackName = CreatePlayerIndexInputBinding(HeavyAttackActionName, PlayerIndex);
	InputComponent->BindAction(HeavyAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnHeavyAttackPressed);
	InputComponent->BindAction(HeavyAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnHeavyAttackReleased);

	static const FName SpecialAttackActionName = FName(UEnum::GetDisplayValueAsText(EInputActions::Special).ToString());
	const FName SpecialAttackName = CreatePlayerIndexInputBinding(SpecialAttackActionName, PlayerIndex);
	InputComponent->BindAction(SpecialAttackName, EInputEvent::IE_Pressed, this, &ABasePlayerController::OnSpecialAttackPressed);
	InputComponent->BindAction(SpecialAttackName, EInputEvent::IE_Released, this, &ABasePlayerController::OnSpecialAttackReleased);
}

#pragma region Input Binding Methods

void ABasePlayerController::OnHorizontalAxisChange(float AxisValue)
{
	InputActionKeyDictionary[EInputActions::Right] = AxisValue > 0.f;
	InputActionKeyDictionary[EInputActions::Left] = AxisValue < 0.f;
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
	InputActionKeyDictionary[EInputActions::MediumAttack] = true;
}

void ABasePlayerController::OnMediumAttackReleased()
{
	InputActionKeyDictionary[EInputActions::MediumAttack] = false;
}

void ABasePlayerController::OnHeavyAttackPressed()
{
	InputActionKeyDictionary[EInputActions::HeavyAttack] = true;
}

void ABasePlayerController::OnHeavyAttackReleased()
{
	InputActionKeyDictionary[EInputActions::HeavyAttack] = false;
}

void ABasePlayerController::OnSpecialAttackPressed()
{
	InputActionKeyDictionary[EInputActions::Special] = true;
}

void ABasePlayerController::OnSpecialAttackReleased()
{
	InputActionKeyDictionary[EInputActions::Special] = false;
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
