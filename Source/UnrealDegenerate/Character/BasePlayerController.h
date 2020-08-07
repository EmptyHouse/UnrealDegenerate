// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "../InputTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DataTable.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDEGENERATE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

	ABasePlayerController(const FObjectInitializer& ObjectInitializer);

public:

	static const FName HorizontalAxisName;

	static const FName VerticalAxisName;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

public:

	UFUNCTION(BlueprintPure)
	bool IsInputKeyPressed(const EInputActions KeyToEvaluate) const;

	UFUNCTION()
	void ClearInputActionDictionary();

protected:

	// Dictionary mapping input action keys with their respective states (false = released, true = depressed)
	UPROPERTY(Transient)
	TMap<EInputActions, bool> InputActionKeyDictionary;

protected:

	#pragma region Input Binding Methods

	UFUNCTION()
	void OnHorizontalAxisChange(float AxisValue);
	
	UFUNCTION()
	void OnVerticalAxisChange(float AxisValue);

	UFUNCTION()
	void OnLightAttackPressed();

	UFUNCTION()
	void OnLightAttackReleased();

	UFUNCTION()
	void OnMediumAttackPressed();

	UFUNCTION()
	void OnMediumAttackReleased();

	UFUNCTION()
	void OnHeavyAttackPressed();

	UFUNCTION()
	void OnHeavyAttackReleased();

	UFUNCTION()
	void OnSpecialAttackPressed();

	UFUNCTION()
	void OnSpecialAttackReleased();

#pragma endregion Input Binding Methods
	
	UFUNCTION()
	FPlayerInputPacket ConstructInputPacketFromKeyDictionary();

};
