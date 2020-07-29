// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "InputTypes.generated.h"

UENUM(BlueprintType)
enum class InputActions : uint8
{
	Left UMETA(DisplayName = "Left"),
	
	Right UMETA(DisplayName = "Right"),

	Up UMETA(DisplayName = "Up"),

	Down UMETA(DisplayName = "Down"),

	LightAttack UMETA(DisplayName = "Light Attack"),

	MediumAttack UMETA(DisplayName = "Medium Attack"),

	HeavyAttack UMETA(DisplayName = "Heavy Attack"),

	Special UMETA(Display Name = "Special")
};

USTRUCT(BlueprintType)
struct FPlayerInputPacket
{
	GENERATED_BODY()

	uint32 InputFrameNumber;

	uint8 PlayerIndex;

	uint32 FrameNumber;

	// Pattern: 
		// Bit 0: LP
		// Bit 1: MP
		// Bit 2: HP
		// Bit 3: LK
		// Bit 4: MK
		// Bit 5: HK
		// Bit 6: Left Directional Input
		// Bit 7: Right Directional Input
		// Bit 8: Up Directional Input
		// Bit 9: Down Directional Input
	uint16 InputPattern;

	/// <summary>
	///  Returns true if this input packet is relevant (i.e. A valid input was recorded during the frame)
	/// </summary>
	bool ShouldBeProcessed();
};
