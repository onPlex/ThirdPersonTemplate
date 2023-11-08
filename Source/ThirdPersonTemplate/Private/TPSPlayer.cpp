// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PBullet.h"


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

	//�޽�������Ʈ ����
	weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	//ĳ���� �޽��� ����  
	weaponMeshComp->SetupAttachment(GetMesh(),FName("Character1_RightHandSocket"));

	fireCoolTime = 1.85f;
	fireTimerTime = 0;
	fireReady = true;
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

	/*
	//[]() -> �͸� �Լ�
	// �Լ� -> Uknown ,void �� �ٸ���.
	auto lamdaFunc = []()->void {
		UE_LOG(LogTemp, Warning, TEXT("Lamda Lamda"));
		};
		//��ġ, ��������ó�� ������ ��
	lamdaFunc();
	*/

	/*
	int32 sum = 10;
	auto lamdaFunc = [&sum](int number)-> void
		{
			sum += number;
		};

	lamdaFunc(20);
	UE_LOG(LogTemp, Warning, TEXT("SUM : %d"), sum);
	*/

	/*
	TArray<int32> Numbers = { 1,2,3,4,5,6,7,8,9,10 };
	TArray<int32> EvenNumbers;

	for (int i = 0; i < Numbers.Num(); i++)
	{
		if (Numbers[i] % 2 == 0) // -> 2�� ������ ��������, 0�̸� --> ¦��
		{
			//c++ , Array != TArray == stl::vector
			EvenNumbers.Add(Numbers[i]);
			//Numbers , i ��°�� ¦���̴ϱ� , EvenNumbers �迭�� ADD
		}
	}
	// EvenNumbers = { 2,4,6,8,10}

	//���ٽ�
	auto PrintNumber = [](int number)
		{
			UE_LOG(LogTemp, Warning, TEXT("Numbers : %d"), number);
		};

	UE_LOG(LogTemp, Warning, TEXT("Even Numbers ...."));
	for (int32 Num : EvenNumbers)  // ex) 1:2 -> ratio / �� / ���� �ݺ�
	{
		PrintNumber(Num);
	}
	*/

	/*
	auto calculator = [](int x, int y, char op)->int{
			// op ���ڿ��� ���� ����� ���� �޸� �Ѵ�
			switch (op)
			{
			case '+':
				return x + y;
			case '-':
				return x - y;
			case '*':
				return x * y;
			case '/':
				//�������� ������ 0 ���� 
				if (y != 0) // 0�� �ƴҶ�, �Ϲ����� ������ 
				{
					return x / y;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Error : Division by zero."));
					return 0;
				}
			default:
				UE_LOG(LogTemp, Warning, TEXT("Error : Invalid operator"));
				return 0;
			}
		};


	int a = 10, b = 5;
	char operation = '*';

	int answer = calculator(a, b, operation);
	UE_LOG(LogTemp, Warning, TEXT("answer : %d"), answer);
	*/
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Locomotion();

	if (!fireReady)
	{
		FireCoolTimer(fireCoolTime, DeltaTime);
	}
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
		EnhancedInputComponent->BindAction(FireIA, ETriggerEvent::Triggered, this, &ATPSPlayer::InputFire);
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

void ATPSPlayer::InputFire(const FInputActionValue& Value)
{
	if (fireReady)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(attackAnimMontage);
		}

		fireReady = false;
	}
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

void ATPSPlayer::FireCoolTimer(float Duration, float deltaTime)
{
	if (fireTimerTime < Duration)
	{
		fireTimerTime+= deltaTime;
    }
	else
	{
		fireTimerTime = 0;
		fireReady = true;
	}
}

void ATPSPlayer::SpawnBullet()
{
	FTransform firePostion = weaponMeshComp->GetSocketTransform(TEXT("FirePostion"));
	GetWorld()->SpawnActor<APBullet>(magazine, firePostion);
}

