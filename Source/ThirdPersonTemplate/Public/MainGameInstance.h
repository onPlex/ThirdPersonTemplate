// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

     //플레이어 돈을 담을 변수 
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	 int64 PlayerMoney;

	 //플레이어 아이템(맵) 담을 변수
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	 TMap<FName, int> PlayerItems;

public:
	 UFUNCTION(BlueprintCallable)
	 void PullPlayerMoney();

	 UFUNCTION(BlueprintCallable)
	 void PushPlayerMoney();
};
