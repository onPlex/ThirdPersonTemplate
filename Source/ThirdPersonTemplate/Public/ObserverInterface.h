// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObserverInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObserverInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THIRDPERSONTEMPLATE_API IObserverInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//옵저버에게 공격 알림을 전달하는 함수
	virtual void NotifyAttack() = 0;
};
