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
   int32* ExistingQuantity = InvetoryMap.Find(ItemName);
   if (ExistingQuantity)
   {
       //�̹� �ش� �������� �κ��丮�� �ִ� ��� ���� ����
      *ExistingQuantity += Quantity;
   }
   else
   {
	   //���ο� �������� �κ��丮�� �߰�
	   InvetoryMap.Add(ItemName, Quantity);
   }
}

void UInventoryComp::RemoveItem(const FName& ItemName, int32 Quantity)
{
    int32* ExistingQuantity = InvetoryMap.Find(ItemName);
	if (ExistingQuantity)
	{
		//�ش� �������� �κ��丮�� ������ ���� ����
		*ExistingQuantity -= Quantity;
		if (*ExistingQuantity <= 0)
		{
			InvetoryMap.Remove(ItemName);
		}
	}
}

int32 UInventoryComp::GetItemQuantiy(const FName& ItemName) const
{
    const int32* ExistingQuantity = InvetoryMap.Find(ItemName);
	return ExistingQuantity ? *ExistingQuantity : 0;

	/*
	���� ������ 

	���ǽ� ? ��1 , ��2 
	true -> ��1
	false -> ��2
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

