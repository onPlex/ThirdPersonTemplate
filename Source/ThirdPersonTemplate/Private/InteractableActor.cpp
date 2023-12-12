// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractableActor::Interact_Implementation(AActor* OtherActor)
{
	// 상호작용 시 행동하는 코드 작성
	// 예: 물체와 상호작용하는 로직

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (TEXT("Interface ,%s"), *OtherActor->GetName()));
}

