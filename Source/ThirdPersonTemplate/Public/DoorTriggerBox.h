// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorTriggerBox.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API ADoorTriggerBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorTriggerBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapLevelLoadBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OhterComp, int32 OthterBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* colliderComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* niagaraFxComp;

public:
	UPROPERTY(EditAnywhere, Category = "Level")
	FName levelToLoad;

	UPROPERTY(EditAnywhere, Category = "Level")
	FName levelToUnLoad;

public:
	void LevelStreming(bool stream);

	void AttractorControl();
public:

	UPROPERTY(EditAnywhere, Category = "MainFunction")
	bool bForStream;
	UPROPERTY(EditAnywhere, Category = "Level")
	bool bLoad;

	UPROPERTY(EditAnywhere, Category = "MainFunction")
	bool bForAttractorControl;

	UPROPERTY(EditAnywhere, Category = "AttractorControl")
	class AActor* attractorActor; 
	UPROPERTY(EditAnywhere, Category = "AttractorControl")
	FVector movePoint;
};
