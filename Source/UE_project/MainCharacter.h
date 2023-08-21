// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class UE_PROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;
	UPROPERTY(VisibleAnywhere)
		FTimerHandle TimerHandle_PrimaryAttack;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack();

	void PrimaryAttack_TimeElapsed();

	void MoveForward(float value);

	void MoveRight(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
