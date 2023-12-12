// Fill out your copyright notice in the Description page of Project Settings.


#include "Goblin.h"

AGoblin::AGoblin()
{
	// ������ ����
}

void AGoblin::Attack_Implementation()
{
	// ��� ���� ���� ��� ����
	UE_LOG(LogTemp, Warning, TEXT("Goblin Enemy is attacking!"));

	// ���� �ɷ��� ����ϸ� ���������� �˸��� �����ϴ�.
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
	// ��� ���� ��� ��� ����
	UE_LOG(LogTemp, Warning, TEXT("Goblin Enemy is defending!"));
}

void AGoblin::NotifyAttack()
{

}

void AGoblin::RegisterObserver(IObserverInterface* Observer)
{
	// ������ ���
	Observers.AddUnique(Observer);
}

void AGoblin::UnregisterObserver(IObserverInterface* Observer)
{
	// ������ ����
	Observers.Remove(Observer);
}