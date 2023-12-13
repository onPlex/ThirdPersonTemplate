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
		ActuralResource = NewObject<UMyConcreteResource>();//���� ���ҽ� ����
		ActuralResource->LoadResource();
	}
}

void UMyResourceProxy::UseResource()
{
	if (!ActuralResource)
	{
		LoadResource(); //���ҽ��� �ε���� �ʾҴٸ� �ε�
	}
	ActuralResource->UseResource(); //���ҽ� ���
}

UMyResourceProxy::~UMyResourceProxy()
{
	if (ActuralResource)
	{
		ActuralResource->ConditionalBeginDestroy(); // ���� ���ҽ� ����
		ActuralResource = nullptr;
	}
}
