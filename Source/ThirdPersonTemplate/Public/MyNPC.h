// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyNPC.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API AMyNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyNPC();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* cameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Interaction")
	class UBoxComponent* triggerBox;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void OverlapBeginTB(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OhterComp, int32 OthterBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSubclassOf<class UItemShop> WidgetRef;
	UPROPERTY()
	class UItemShop* itemshopWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	TArray<FName>items;
};
