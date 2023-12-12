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
		// 이미 해당 아이템이 인벤토리에 있는 경우 수량 증가
		*ExistingQuantity += Quantity;
	}
	else
	{
		// 새로운 아이템을 인벤토리에 추가
		InventoryMap.Add(ItemName, Quantity);
	}
}

void UInventoryComp::RemoveItem(const FName& ItemName, int32 Quantity)
{
	int32* ExistingQuantity = InventoryMap.Find(ItemName);
	if (ExistingQuantity)
	{
		// 해당 아이템이 인벤토리에 있으면 수량 감소
		*ExistingQuantity -= Quantity;
		if (*ExistingQuantity <= 0)
		{
			// 수량이 0 이하이면 아이템 삭제
			InventoryMap.Remove(ItemName);
		}
	}
}

int32 UInventoryComp::GetItemQuantity(const FName& ItemName) const
{
	const int32* ExistingQuantity = InventoryMap.Find(ItemName);
	return ExistingQuantity ? *ExistingQuantity : 0;
	/*
	삼항 연산자

		이 표현식은 다음과 같은 의미를 가집니다:

		ExistingQuantity가 NULL이 아닌 경우(즉, 해당 아이템이 인벤토리에 존재하는 경우):
		ExistingQuantity가 가리키는 정수값을 반환(*ExistingQuantity: 포인터가 가리키는 값)

		ExistingQuantity가 NULL인 경우(즉, 해당 아이템이 인벤토리에 없는 경우):0을 반환
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

