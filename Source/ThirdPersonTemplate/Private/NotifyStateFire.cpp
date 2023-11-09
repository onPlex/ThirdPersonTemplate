// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStateFire.h"

///Notify 가 불려지는 시작 첫(1) 프레임
void UNotifyStateFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("NotifyBegin"));

	//접근을 위해서 , 플레이어 캐릭터를 알아야 한다
	//MeshComp -> 해당 애니메이션을 플레이하는, 스켈레탈 메쉬 
	tpsPlayer = Cast<ATPSPlayer>(MeshComp->GetOwner());
	
	//캐릭터가 총알을 생성한다 
	if (tpsPlayer)
	{   //총알 생성하기
		tpsPlayer->SpawnBullet();
	}
}

///Notify 가 불려지는 동안의 매 프레임 
void UNotifyStateFire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("NotifyTick"));
}

///Notify 가 끝나는 (1) 프레임 
void UNotifyStateFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NotifyEnd"));
}
