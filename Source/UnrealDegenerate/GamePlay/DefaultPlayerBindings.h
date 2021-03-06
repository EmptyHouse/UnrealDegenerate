// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "../InputTypes.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "DefaultPlayerBindings.generated.h"


USTRUCT(BlueprintType)
struct FPlayerInputBinding : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FKey PlayerOneActionBindKey;

	UPROPERTY(EditDefaultsOnly)
	FKey PlayerTwoActionBindKey;

};

USTRUCT(BlueprintType)
struct FPlayerAxisBinding : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditDefaultsOnly)
	FKey PlayerOnePositiveAxisBindingKey;

	UPROPERTY(EditDefaultsOnly)
	FKey PlayerOneNegativeAxisBindingKey;

	UPROPERTY(EditDefaultsOnly)
	FKey PlayerTwoPositiveAxisBindingKey;

	UPROPERTY(EditDefaultsOnly)
	FKey PlayerTwoNegativeAxisBindingKey;
};

/**
 * 
 */
UCLASS(Blueprintable)
class UNREALDEGENERATE_API UDefaultInputProperties : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	UDataTable* DefaultInputAxisBindings;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* DefaultInputActionBindings;
	
};
