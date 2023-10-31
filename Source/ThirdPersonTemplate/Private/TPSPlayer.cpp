// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-88),FRotator(0,-90,0));
	}

	//springArm ���� - �ʱ�ȭ 
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0,0,50),FRotator(-20,0,0));
	springArmComp->TargetArmLength = 530;

	//ī�޶� ���� - �ʱ�ȭ
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

