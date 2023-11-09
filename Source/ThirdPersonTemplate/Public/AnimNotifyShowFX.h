// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TPSPlayer.h"
#include "AnimNotifyShowFX.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UAnimNotifyShowFX : public UAnimNotify
{
	GENERATED_BODY()
	

	UPROPERTY()
	ATPSPlayer* tpsPlayer;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
