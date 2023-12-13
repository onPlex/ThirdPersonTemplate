// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyResourceInterface.h"
#include "MyResourceProxy.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UMyResourceProxy : public UObject,
public IMyResourceInterface
{
	GENERATED_BODY()

private: 

	class UMyConcreteResource* ActuralResource; //실제 리소스에 대한 포인터

	public: 
		UMyResourceProxy();

		virtual void LoadResource() override;
		virtual void UseResource() override;
		
		~UMyResourceProxy(); //소멸자에서 실제 리소스 정리
};
