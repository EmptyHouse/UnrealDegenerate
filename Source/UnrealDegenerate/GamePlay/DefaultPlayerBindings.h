// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Engine/DataTable.h"
#include "DefaultPlayerBindings.generated.h"


USTRUCT(BlueprintType)
struct FPlayerInputBinding : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName ActionName;

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
	FName AxisName;

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
class UNREALDEGENERATE_API UDefaultPlayerBindings : public UDataTable
{
	GENERATED_BODY()
	
};
