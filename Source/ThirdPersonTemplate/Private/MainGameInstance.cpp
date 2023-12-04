// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TPSPlayer.h"

//GameInstance.playerMoney --> TPSPlayer.money 
void UMainGameInstance::PullPlayerMoney()
{
    ATPSPlayer * myPlayer = Cast<ATPSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

    if (myPlayer)
    {
        myPlayer->money = PlayerMoney;
    }
}

//TPSPlayer.money --> GameInstance.playerMoney
void UMainGameInstance::PushPlayerMoney()
{
    ATPSPlayer* myPlayer = Cast<ATPSPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (myPlayer)
    {
        PlayerMoney = myPlayer->money;
    }
}
