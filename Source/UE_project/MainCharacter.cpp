// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent->SetupAttachment(SpringArmComponent);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::Attack() {

	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMainCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	
}

void AMainCharacter::PrimaryAttack_TimeElapsed() {

	// 生成角度和坐标
	// 获取人物模型中手的坐标，GetSocketLocation可以获取骨骼中的插件
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	// 未校正前的生成方位
	const FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	// 无论任何情况都生成（无视重叠，碰撞，覆盖...）
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 将角色自身作为触发者传入，以便子弹判断正确的交互对象
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	//// 碰撞参数，忽略自身
	//FCollisionQueryParams Params;
	//Params.AddIgnoredActor(this);

	//// 获取Camera组件
	//APlayerCameraManager* CurrentCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	//// 方向是摄像机视角的正前方（屏幕正中央），这里不要把手部模型的坐标传入，方向会偏
	//FVector TraceDirection = CurrentCamera->GetActorForwardVector();
	//// 起始位置是摄像机的位置
	//FVector TraceStart = CurrentCamera->GetCameraLocation();
	//// 终点是一段距离，后面的5000不固定
	//FVector TraceEnd = TraceStart + (TraceDirection * 5000);

	//FHitResult Hit;
	//// Line Trace检测与障碍物的撞击点
	//if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_GameTraceChannel1, Params))
	//{
	//	// 将撞击点作为方向向量的终点位置
	//	TraceEnd = Hit.ImpactPoint;
	//}
	//// 起始点是我们的子弹生成点（手），终点是目标点，获得Rotation
	//FRotator ProjRotation = (TraceEnd - HandLocation).Rotation();
	//// 最终获得校正后的生成方位
	//FTransform SpawnTM = FTransform(ProjRotation, HandLocation);

	// 在世界中生成
}

void AMainCharacter::MoveForward(float value) {
	FRotator ControlRotation = GetControlRotation();

	ControlRotation.Roll = 0.f;
	ControlRotation.Pitch = 0.f;

	const FVector ForwardDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection,value);
}
void AMainCharacter::MoveRight(float value) {
	FRotator ControlRotation = GetControlRotation();

	ControlRotation.Roll = 0.f;
	ControlRotation.Pitch = 0.f;

	const FVector RightDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value);
}


// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

}

