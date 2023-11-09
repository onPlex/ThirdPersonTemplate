// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyShowFX.h"
void UAnimNotifyShowFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{     
	tpsPlayer = Cast<ATPSPlayer>(MeshComp->GetOwner());

	if (tpsPlayer)
	{
	   tpsPlayer->ShowFX();
	}
}
