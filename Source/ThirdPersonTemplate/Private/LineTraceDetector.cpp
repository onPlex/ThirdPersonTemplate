// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTraceDetector.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULineTraceDetector::ULineTraceDetector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULineTraceDetector::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void ULineTraceDetector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULineTraceDetector::PeformLineTrace()
{
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = StartLocation + GetOwner()->GetActorForwardVector() * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		CollisionParams
	);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Magenta, false, 3.0f);
	if (bHit) //hit 가 있다면,
	{
		OnLineTraceHit(HitResult);
	}
}

void ULineTraceDetector::OnLineTraceHit(FHitResult HitResult)
{
	if (HitResult.GetActor() && HitResult.GetActor()->IsA(ActorClassToTrace))
	{
		//원하는 클래스의 액터를 찾은 경우 
		AActor* FoundActor = HitResult.GetActor();
		//여기서 원하는 작업
		if (FoundActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (TEXT("%s"), *FoundActor->GetName()));
		}
	}
}

