// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"

DECLARE_DELEGATE(FOnBossDiedDelegate);

UCLASS()
class UE_PROJECT_API ABossActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void HandleBossDiedEvent();
	UPROPERTY(EditInstanceonly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnBossDiedDelegate OnBossDied;

};
