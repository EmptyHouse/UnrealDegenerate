// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "InputTypes.generated.h"

UENUM(BlueprintType)
enum class EInputActions : uint8
{
	None UMETA(Hidden),

	Left = 0x15,

	Right = 0x20,

	Up = 0x40,

	Down = 0x80,

	LightAttack = 0x01,

	MediumAttack = 0x02,

	HeavyAttack = 0x04,

	Special = 0x08
};

USTRUCT(BlueprintType)
struct FPlayerInputPacket
{
	GENERATED_BODY()

	FPlayerInputPacket() {

	}

	FPlayerInputPacket(const uint32 FrameNumber, const uint8 PlayerIndex, const uint8 InputPattern) :
		InputFrameNumber(FrameNumber),
		PlayerIndex(PlayerIndex),
		InputPattern(InputPattern) {}

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

	uint8 GetPlayerIndex() const { return PlayerIndex; }

	bool IsInputKeyPressed(const EInputActions InputAction) const { return (bool)(InputPattern & (uint8)(InputAction)); }
};
