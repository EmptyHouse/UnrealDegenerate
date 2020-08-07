// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "InputTypes.generated.h"

UENUM(BlueprintType)
enum class EInputActions : uint8
{
	Left,
	
	Right,

	Up,

	Down,

	LightAttack,

	MediumAttack,

	HeavyAttack,

	Special
};

USTRUCT(BlueprintType)
struct FPlayerInputPacket
{
	GENERATED_BODY()

	uint32 InputFrameNumber;

	uint8 PlayerIndex;

	// Pattern: 
		// Bit 0: LP
		// Bit 1: MP
		// Bit 2: HP
		// Bit 3: SP
		// Bit 4: Left Directional Input
		// Bit 5: Right Directional Input
		// Bit 6: Up Directional Input
		// Bit 7: Down Directional Input
	uint8 InputPattern;

	/// <summary>
	///  Returns true if this input packet is relevant (i.e. A valid input was recorded during the frame)
	/// </summary>
	bool ShouldBeProcessed();
};
