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

void ULineTraceDetector::PerformLineTrace()
{
    FVector StartLocation = GetOwner()->GetActorLocation();
    FVector EndLocation = StartLocation + GetOwner()->GetActorForwardVector() * TraceDistance;

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    // ���� Ʈ���̽� ����
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility,
        CollisionParams
    );

    if (bHit)
    {
        // ���� Ʈ���̽��� �浹�� ���
        OnLineTraceHit(HitResult);
    }
}

void ULineTraceDetector::OnLineTraceHit(FHitResult HitResult)
{
    if (HitResult.GetActor() && HitResult.GetActor()->IsA(ActorClassToTrace))
    {
        // ���ϴ� Ŭ������ ���͸� ã�� ���
        AActor* FoundActor = HitResult.GetActor();
        // ���⼭ ���ϴ� �۾��� �����ϰų� �ش� ���͸� ����� �� �ֽ��ϴ�.
        if (FoundActor)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (TEXT("%s"), *FoundActor->GetName()));
        }
    }
}

