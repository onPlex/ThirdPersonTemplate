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

	//발사체 컴포넌트 생성
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	// 발사체 컴포넌트를 update 시킬 컴포넌트 지정, 
	// update == tick, update ->매프레임 연산하겠다
	movementComp->SetUpdatedComponent(collisionComp);
	// 초기속도
	movementComp->InitialSpeed = 3000.f;
	// 최대속도
	movementComp->MaxSpeed = 5000.f;
	// 반동,
	movementComp->bShouldBounce = true;
	// 반동 크기
	movementComp->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void APBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

