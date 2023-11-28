// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemShop.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UItemShop : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	class ANPC* owenerNPC;
};
