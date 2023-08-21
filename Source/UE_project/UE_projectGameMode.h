// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE_projectGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);


UCLASS(minimalapi)
class AUE_projectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE_projectGameMode();

	const FOnPlayerDiedSignature& GetOnPlayerDied() const {
		return OnPlayerDied;
	}

	virtual void RestartPlayer(AController* NewPlayer) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void PlayerDied(ACharacter* Character);
	UPROPERTY()
		FOnPlayerDiedSignature OnPlayerDied;
};



