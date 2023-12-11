// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

AEnemy::AEnemy()
{
	//생성자 구현
}

void AEnemy::Attack_Implementation()
{
	//적의 공격 기능 구현
	UE_LOG(LogTemp, Warning, TEXT("Enemy is attacking!"));
}

void AEnemy::Defend_Implementation()
{
	//적의 방어 기능 구현
	UE_LOG(LogTemp, Warning, TEXT("Enemy is defending!"));
}
