// Copyright © 2020 Fucking Degenerate Games Inc.

#pragma once

#include "CoreMinimal.h"
#include "../InputTypes.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DataTable.h"
#include "BasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPacketReady, const FPlayerInputPacket&, InputPacketToExecute);

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

	FOnPlayerPacketReady OnPlayerPacketReady;

private:

	TQueue<FPlayerInputPacket> InputQueue;

	UPROPERTY(Transient)
	uint8 PreviousInputPattern;

	UPROPERTY(Transient)
	uint8 CurrentInputPattern;

	UPROPERTY(Transient)
	uint8 PlayerID = -1;

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

};
