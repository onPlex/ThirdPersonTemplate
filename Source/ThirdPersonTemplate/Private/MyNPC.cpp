// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPC.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "ItemShop.h"

// Sets default values
AMyNPC::AMyNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	cameraComp->SetupAttachment(RootComponent);
	cameraComp->SetRelativeLocation(FVector(180, 0, 0));
	cameraComp->SetRelativeRotation(FRotator(0, 180, 0));
	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("triggerBox"));
	triggerBox->SetupAttachment(RootComponent);
	triggerBox->SetBoxExtent(FVector(0, 100, 50));
	triggerBox->SetRelativeLocation(FVector(100, 0, 0));
}

// Called when the game starts or when spawned
void AMyNPC::BeginPlay()
{
	Super::BeginPlay();
	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMyNPC::OverlapBeginTB);

}

// Called every frame
void AMyNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyNPC::OverlapBeginTB(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OhterComp, int32 OthterBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (WidgetRef) {
		itemshopWidget = CreateWidget<UItemShop>(GetWorld(), WidgetRef);
		if (itemshopWidget)itemshopWidget->AddToViewport();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("NPC OverlapBeginTB"));
	//APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	OurPlayerController->SetViewTargetWithBlend(this, 1.f);
	OurPlayerController->SetInputMode(FInputModeUIOnly());
	OurPlayerController->SetShowMouseCursor(true);
}

