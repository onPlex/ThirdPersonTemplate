// Fill out your copyright notice in the Description page of Project Settings.


#include "PBullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
APBullet::APBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	collisionComp->SetSphereRadius(13);
	RootComponent = collisionComp;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(collisionComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//�߻�ü ������Ʈ ����
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	// �߻�ü ������Ʈ�� update ��ų ������Ʈ ����, 
	// update == tick, update ->�������� �����ϰڴ�
	movementComp->SetUpdatedComponent(collisionComp);
	// �ʱ�ӵ�
	movementComp->InitialSpeed = 3000.f;
	// �ִ�ӵ�
	movementComp->MaxSpeed = 5000.f;
	// �ݵ�,
	movementComp->bShouldBounce = true;
	// �ݵ� ũ��
	movementComp->Bounciness = 0.3f;

	//���� ���� (����, ��)
	//InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void APBullet::BeginPlay()
{
	Super::BeginPlay();

	//Ÿ�̸� ���� �ϴ� ���� ~= �˶�, �𸮾� ��� (Tool)
	FTimerHandle deathTimer; 
	//GetWorld()->GetTimerManager().SetTimer(deathTimer,this,&APBullet::Die, 2.0f,false);
	//(�˸�, �˸�ó���� �� ��ü, �˸� ó�� �Լ�, �˸� �ð�, �ݺ� ����, ù ȣ�� �� ������ �ð�)

	//FTimerDelegate ~= �𸮾� Timer���� delegate�� �����ϴ� Ŭ���� 
	GetWorld()->GetTimerManager().SetTimer(deathTimer,FTimerDelegate::CreateLambda([this]()->void{Destroy();}), 2.0f,false);
}

// Called every frame
void APBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void APBullet::Die()
//{
//	Destroy();
//}

