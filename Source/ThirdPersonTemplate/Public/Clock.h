// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
	float CurrentDay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
	float CurrentHour;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
	float CurrentMinute;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time")
	float CurrentSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float TotalSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float TimeScale = 1;

	//현재시각 문자로 반환하는 함수
	UFUNCTION(BlueprintCallable)
	FString GetTimeByTotalSec(float totlaSec);

	UPROPERTY(EditAnywhere, Category = "Sun")
	class AActor* Sun;


	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color3;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color6;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color9;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color12;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color15;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color18;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color21;
	UPROPERTY(EditAnywhere, Category = "Sun")
	FLinearColor Color24;

protected:
	void UpdateTime(float DeltaSec);

	void RotateDirectionalLightWithTime(AActor* OwningActor);
};
