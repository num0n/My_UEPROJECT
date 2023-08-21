// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE_projectGameMode.h"
#include "UE_projectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_projectGameMode::AUE_projectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AUE_projectGameMode::BeginPlay() {

	Super::BeginPlay();

	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &AUE_projectGameMode::PlayerDied);
	}
}

void AUE_projectGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}

void AUE_projectGameMode::PlayerDied(ACharacter* Character)
{
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);
}