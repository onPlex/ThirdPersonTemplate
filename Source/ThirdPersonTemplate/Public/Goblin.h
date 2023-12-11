// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Goblin.generated.h"

/**
 *
 */
UCLASS()
class THIRDPERSONTEMPLATE_API AGoblin : public AEnemy
{
	GENERATED_BODY()

public:
	AGoblin();

	//적(enemy) 클래스의 추상 함수를 오버라이드하여 구현 
	virtual void Attack_Implementation() override;
	virtual void Defend_Implementation() override;

};
