// Fill out your copyright notice in the Description page of Project Settings.


#include "MyResourceProxy.h"
#include "MyConcreteResource.h"

UMyResourceProxy::UMyResourceProxy()
{
	ActuralResource = nullptr;
}

void UMyResourceProxy::LoadResource()
{
	if (!ActuralResource)
	{
		ActuralResource = NewObject<UMyConcreteResource>();//실제 리소스 생성
		ActuralResource->LoadResource();
	}
}

void UMyResourceProxy::UseResource()
{
	if (!ActuralResource)
	{
		LoadResource(); //리소스가 로드되지 않았다면 로드
	}
	ActuralResource->UseResource(); //리소스 사용
}

UMyResourceProxy::~UMyResourceProxy()
{
	if (ActuralResource)
	{
		ActuralResource->ConditionalBeginDestroy(); // 실제 리소스 제거
		ActuralResource = nullptr;
	}
}
