// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "DefaultPlayerBindings.generated.h"


USTRUCT(BlueprintType)
struct FPlayerInputBinding : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
	FKey PlayerOneActionBindKey;

	UPROPERTY(EditAnywhere)
	FKey PlayerTwoActionBindKey;

};

USTRUCT(BlueprintType)
struct FPlayerAxisBinding : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:

	UPROPERTY(EditAnywhere)
	FKey PlayerOnePositiveAxisBindingKey;

	UPROPERTY(EditAnywhere)
	FKey PlayerOneNegativeAxisBindingKey;

	UPROPERTY(EditAnywhere)
	FKey PlayerTwoPositiveAxisBindingKey;

	UPROPERTY(EditAnywhere)
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

	UPROPERTY(EditAnywhere)
	UDataTable* DefaultInputAxisBindings;

	UPROPERTY(EditAnywhere)
	UDataTable* DefaultInputActionBindings;
	
};
