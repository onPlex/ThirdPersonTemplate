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
       //이미 해당 아이템이 인벤토리에 있는 경우 수량 증가
      *ExistingQuantity += Quantity;
   }
   else
   {
	   //새로운 아이템을 인벤토리에 추가
	   InvetoryMap.Add(ItemName, Quantity);
   }
}

void UInventoryComp::RemoveItem(const FName& ItemName, int32 Quantity)
{
    int32* ExistingQuantity = InvetoryMap.Find(ItemName);
	if (ExistingQuantity)
	{
		//해당 아이템이 인벤토리에 있으면 수량 감소
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
	삼항 연산자 

	조건식 ? 값1 , 값2 
	true -> 값1
	false -> 값2
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

