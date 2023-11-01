// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
ATPSPlayer::ATPSPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ConstructorHelpers ��� ��ƿ��Ƽ�� ���� ��������(ã��)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/MyResource/unitychan.unitychan'"));

	if (initMesh.Succeeded()) //����� ������Ʈ�� �����Դٸ� ~ 
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object);

		//Relative - > ����� ��ġ��, ȸ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	//springArm ���� - �ʱ�ȭ 
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;
	springArmComp->bUsePawnControlRotation = true;

	//ī�޶� ���� - �ʱ�ȭ
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;

	//moveSpeed = 100;
	
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Locomotion();
}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ATPSPlayer::Move);
		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &ATPSPlayer::LookUp);
		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &ATPSPlayer::Turn);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &ATPSPlayer::InputJump);
	}
}

void ATPSPlayer::Move(const FInputActionValue& Value)
{
	const FVector _currentValue = Value.Get<FVector>();

	if (Controller)
	{
	     moveDirection.Y = _currentValue.X;
		 moveDirection.X = _currentValue.Y;
	}
}

void ATPSPlayer::LookUp(const FInputActionValue& Value)
{
     //mouse y - �� ���� �� (float)
	const float _currentValue = Value.Get<float>();
    AddControllerPitchInput(_currentValue);
}

void ATPSPlayer::Turn(const FInputActionValue& Value)
{
	//mouse x  - �� ���� �� (float)
	const float _currentValue = Value.Get<float>();
	AddControllerYawInput(_currentValue);
}

void ATPSPlayer::InputJump(const FInputActionValue& Value)
{
    Jump();
}

void ATPSPlayer::Locomotion()
{
	//�̵������� ��Ʈ�� ���� �������� ��ȯ
	moveDirection = FTransform(GetControlRotation()).TransformVector(moveDirection);

	/*
	//�÷��̾� �̵� - ��ӿ
	FVector P0 = GetActorLocation(); //������ġ
	FVector vt = moveDirection * moveSpeed * DeltaTime; //�̵��Ÿ�
	FVector P = P0 + vt;
	SetActorLocation(P);
	*/

	AddMovementInput(moveDirection);
	//���� �ʱ�ȭ
	moveDirection = FVector::ZeroVector; //ZeroVector; == FVector(0,0,0)
}

