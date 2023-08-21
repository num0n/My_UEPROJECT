// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorToSpawn.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AActorToSpawn::AActorToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	StaticMeshComp = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	ParticleComp = CreateAbstractDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMeshComp->AttachToComponent(SphereComp,FAttachmentTransformRules::KeepRelativeTransform);

	ParticleComp->AttachToComponent(SphereComp,FAttachmentTransformRules::KeepRelativeTransform);

	SphereComp->SetSphereRadius(16.0f);

	StaticMeshComp->SetRelativeLocation(FVector(0.0,0.0,-12.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(0.25,0.25,0.25));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	StaticMeshComp->SetStaticMesh(SphereMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleCompAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	ParticleComp->SetTemplate(ParticleCompAsset.Object);
}

// Called when the game starts or when spawned
void AActorToSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

