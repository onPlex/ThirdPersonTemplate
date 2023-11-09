// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStateFire.h"

///Notify �� �ҷ����� ���� ù(1) ������
void UNotifyStateFire::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("NotifyBegin"));

	//������ ���ؼ� , �÷��̾� ĳ���͸� �˾ƾ� �Ѵ�
	//MeshComp -> �ش� �ִϸ��̼��� �÷����ϴ�, ���̷�Ż �޽� 
	tpsPlayer = Cast<ATPSPlayer>(MeshComp->GetOwner());
	
	//ĳ���Ͱ� �Ѿ��� �����Ѵ� 
	if (tpsPlayer)
	{   //�Ѿ� �����ϱ�
		tpsPlayer->SpawnBullet();
	}
}

///Notify �� �ҷ����� ������ �� ������ 
void UNotifyStateFire::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("NotifyTick"));
}

///Notify �� ������ (1) ������ 
void UNotifyStateFire::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NotifyEnd"));
}
