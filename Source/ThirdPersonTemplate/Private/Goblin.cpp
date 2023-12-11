// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

AGoblin::AGoblin()
{
	//생성자 구현
}

void AGoblin::Attack_Implementation()
{
	//적의 공격 기능 구현
	UE_LOG(LogTemp, Warning, TEXT("Goblin is attacking!"));
}

void AGoblin::Defend_Implementation()
{
	//적의 방어 기능 구현
	UE_LOG(LogTemp, Warning, TEXT("Goblin is defending!"));
}
