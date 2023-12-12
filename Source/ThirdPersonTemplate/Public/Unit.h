// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Unit.generated.h"

UCLASS()
class THIRDPERSONTEMPLATE_API AUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnit();

	// 추상 함수로 선언하여 파생 클래스에서 구현하도록 함
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit")
	void Attack();
	virtual void Attack_Implementation() PURE_VIRTUAL(AUnit::Attack_Implementation);
	/*UFUNCTION(BlueprintNativeEvent): 이 매크로는 Unreal Engine에서 블루프린트와 상호작용하는 함수로 정의. 이 함수는 네이티브(C++) 구현과 블루프린트 구현 모두를 가질 수 있음. 블루프린트에서 이 함수를 오버라이드하거나 호출할 수 있음.*/

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit")
	void Defend();
	virtual void Defend_Implementation() PURE_VIRTUAL(AUnit::Defend_Implementation);
	/*PURE_VIRTUAL(AUnit::Defend_Implementation);: 이 부분은 함수의 가상 함수 구현을 정의. PURE_VIRTUAL 매크로는 이 함수가 순수 가상 함수임. 순수 가상 함수는 구현이 없으며 파생 클래스에서 반드시 오버라이드되어야 함. 따라서 AUnit 클래스를 상속하는 클래스는 Defend_Implementation 함수를 반드시 구현해야 함.
	*/


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
