// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyResourceInterface.h"
#include "MyConcreteResource.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEMPLATE_API UMyConcreteResource : public UObject,
public IMyResourceInterface
{
	GENERATED_BODY()

	public:

	virtual void LoadResource() override;

	virtual void UseResource() override;
	
};
