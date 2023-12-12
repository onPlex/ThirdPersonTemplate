// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComp.h"

// Sets default values for this component's properties
UInventoryComp::UInventoryComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComp::AddItem(const FName& ItemName, int32 Quantity)
{
	int32* ExistingQuantity = InventoryMap.Find(ItemName);
	if (ExistingQuantity)
	{
		// �̹� �ش� �������� �κ��丮�� �ִ� ��� ���� ����
		*ExistingQuantity += Quantity;
	}
	else
	{
		// ���ο� �������� �κ��丮�� �߰�
		InventoryMap.Add(ItemName, Quantity);
	}
}

void UInventoryComp::RemoveItem(const FName& ItemName, int32 Quantity)
{
	int32* ExistingQuantity = InventoryMap.Find(ItemName);
	if (ExistingQuantity)
	{
		// �ش� �������� �κ��丮�� ������ ���� ����
		*ExistingQuantity -= Quantity;
		if (*ExistingQuantity <= 0)
		{
			// ������ 0 �����̸� ������ ����
			InventoryMap.Remove(ItemName);
		}
	}
}

int32 UInventoryComp::GetItemQuantity(const FName& ItemName) const
{
	const int32* ExistingQuantity = InventoryMap.Find(ItemName);
	return ExistingQuantity ? *ExistingQuantity : 0;
	/*
	���� ������

		�� ǥ������ ������ ���� �ǹ̸� �����ϴ�:

		ExistingQuantity�� NULL�� �ƴ� ���(��, �ش� �������� �κ��丮�� �����ϴ� ���):
		ExistingQuantity�� ����Ű�� �������� ��ȯ(*ExistingQuantity: �����Ͱ� ����Ű�� ��)

		ExistingQuantity�� NULL�� ���(��, �ش� �������� �κ��丮�� ���� ���):0�� ��ȯ
	*/

}


// Called when the game starts
void UInventoryComp::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UInventoryComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

