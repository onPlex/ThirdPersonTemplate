// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "TPSPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorTriggerBox::ADoorTriggerBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	colliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(colliderComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(colliderComp);

	niagaraFxComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FxComp"));
	niagaraFxComp->SetupAttachment(colliderComp);
}

// Called when the game starts or when spawned
void ADoorTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
	colliderComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorTriggerBox::OverlapLevelLoadBegin);
}

void ADoorTriggerBox::OverlapLevelLoadBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OhterComp, int32 OthterBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Collision"));
   ATPSPlayer* _myCharacter = Cast<ATPSPlayer>(OtherActor);

   if (bForStream)
   {
	   if (OtherActor && levelToLoad != "")
	   {
		   LevelStreming(bLoad);
	   }
   }
   else if (bForAttractorControl)
   {
	  // AttractorControl();
   }
   else if (bForStream && bForAttractorControl)
   {
	 //  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Please Uncheck One"));
   }
}

// Called every frame
void ADoorTriggerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorTriggerBox::LevelStreming(bool stream)
{
	FLatentActionInfo LactentInfo; //로딩 과정 결과 따위의 정보들을 가지고 있는 구조체
	if (stream)
	{
		UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, LactentInfo);
	}
	else
	{
		UGameplayStatics::UnloadStreamLevel(this, levelToLoad, LactentInfo, true);
	}	
	//UGameplayStatics::OpenLevel(this, levelToLoad);
	//UGameplayStatics::UnloadStreamLevel(this, levelToLoad, LactentInfo, false);
	//UGameplayStatics::UnloadStreamLevel(this, levelToLoad, LactentInfo, true);
}

void ADoorTriggerBox::AttractorControl()
{
	if (attractorActor)
	{
		//attractorActor->SetActorLocation(movePoint);
	}
}

