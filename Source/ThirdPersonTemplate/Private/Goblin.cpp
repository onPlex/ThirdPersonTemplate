// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

AGoblin::AGoblin()
{
	// 생성자 구현
}

void AGoblin::Attack_Implementation()
{
	// 고블린 적의 공격 기능 구현
	UE_LOG(LogTemp, Warning, TEXT("Goblin Enemy is attacking!"));

	// 공격 능력을 사용하면 옵저버에게 알림을 보냅니다.
	for (IObserverInterface* Observer : Observers)
	{
		if (Observer)
		{
			Observer->NotifyAttack();
		}
	}
}

void AGoblin::Defend_Implementation()
{
	// 고블린 적의 방어 기능 구현
	UE_LOG(LogTemp, Warning, TEXT("Goblin Enemy is defending!"));
}

void AGoblin::NotifyAttack()
{

}

void AGoblin::RegisterObserver(IObserverInterface* Observer)
{
	// 옵저버 등록
	Observers.AddUnique(Observer);
}

void AGoblin::UnregisterObserver(IObserverInterface* Observer)
{
	// 옵저버 제거
	Observers.Remove(Observer);
}