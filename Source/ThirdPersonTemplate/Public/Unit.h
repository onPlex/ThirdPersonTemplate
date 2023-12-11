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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit")
	void Attack();
	virtual void Attack_Implementation() PURE_VIRTUAL(AUnit::Attack_Implementation);
	/*
	UFUNCTION(BlueprintNativeEvent)
	:�� ��ũ�δ� Unreal Engine���� �������Ʈ�� ��ȣ�ۿ��ϴ� �Լ��� ����. 
	 �� �Լ��� ����Ƽ��(C++) ������ �������Ʈ ���� ��θ� ���� �� ����.
	 �������Ʈ���� �� �Լ��� �������̵��ϰų� ȣ���� �� ����.
	*/

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Unit")
	void Defend();
	virtual void Defend_Implementation() PURE_VIRTUAL(AUnit::Defend_Implementation);
	/*
	PURE_VIRTUAL(AUnit::Defend_Implementation); : �� �κ��� �Լ��� ���� �Լ� ������ ����.
	PURE_VIRTUAL ��ũ�δ� �� �Լ��� ���� ���� �Լ����� ��Ÿ��.
	���� ���� �Լ��� ������ ������ �Ļ� Ŭ�������� �ݵ�� �������̵� �ؾ���.
	����, AUnit Ŭ������ ����ϴ� Ŭ������ Defend_Implementation() �Լ��� �ݵ�� �����ؾ� ��.
	*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
