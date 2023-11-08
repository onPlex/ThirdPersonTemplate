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

	// ConstructorHelpers 라는 유틸리티로 에셋 가져오기(찾기)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> initMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/MyResource/unitychan.unitychan'"));

	if (initMesh.Succeeded()) //제대로 오브젝트를 가져왔다면 ~ 
	{
		GetMesh()->SetSkeletalMesh(initMesh.Object);

		//Relative - > 상대적 위치값, 회전값
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	//springArm 생성 - 초기화 
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;
	springArmComp->bUsePawnControlRotation = true;

	//카메라 생성 - 초기화
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;

	//moveSpeed = 100;

	//메쉬컴포넌트 생성
	weaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	//캐릭터 메쉬에 부착  
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
	//[]() -> 익명 함수
	// 함수 -> Uknown ,void 랑 다르다.
	auto lamdaFunc = []()->void {
		UE_LOG(LogTemp, Warning, TEXT("Lamda Lamda"));
		};
		//마치, 지역변수처럼 선언을 함
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
		if (Numbers[i] % 2 == 0) // -> 2로 나누어 나머지가, 0이면 --> 짝수
		{
			//c++ , Array != TArray == stl::vector
			EvenNumbers.Add(Numbers[i]);
			//Numbers , i 번째가 짝수이니까 , EvenNumbers 배열에 ADD
		}
	}
	// EvenNumbers = { 2,4,6,8,10}

	//람다식
	auto PrintNumber = [](int number)
		{
			UE_LOG(LogTemp, Warning, TEXT("Numbers : %d"), number);
		};

	UE_LOG(LogTemp, Warning, TEXT("Even Numbers ...."));
	for (int32 Num : EvenNumbers)  // ex) 1:2 -> ratio / 비 / 대응 반복
	{
		PrintNumber(Num);
	}
	*/

	/*
	auto calculator = [](int x, int y, char op)->int{
			// op 문자열에 따라서 경우의 수를 달리 한다
			switch (op)
			{
			case '+':
				return x + y;
			case '-':
				return x - y;
			case '*':
				return x * y;
			case '/':
				//나누셈은 언제나 0 주의 
				if (y != 0) // 0이 아닐때, 일반적인 나누기 
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
	//mouse y - 한 축의 값 (float)
	const float _currentValue = Value.Get<float>();
	AddControllerPitchInput(_currentValue);
}

void ATPSPlayer::Turn(const FInputActionValue& Value)
{
	//mouse x  - 한 축의 값 (float)
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
	//이동방향을 컨트롤 방향 기준으로 변환
	moveDirection = FTransform(GetControlRotation()).TransformVector(moveDirection);

	/*
	//플레이어 이동 - 등속운동
	FVector P0 = GetActorLocation(); //현재위치
	FVector vt = moveDirection * moveSpeed * DeltaTime; //이동거리
	FVector P = P0 + vt;
	SetActorLocation(P);
	*/

	AddMovementInput(moveDirection);
	//방향 초기화
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

