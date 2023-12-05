// Fill out your copyright notice in the Description page of Project Settings.
#include "Clock.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

#define ONE_YEAR 31104000 // 360�� -> �� 
#define ONE_MONTH 2592000 // 30�� ���� 
#define ONE_DAY 86400 // 24�ð� 
#define ONE_HOUR 3600
#define ONE_MINUTE 60

// Sets default values
AClock::AClock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTime(DeltaTime);

	RotateDirectionalLightWithTime(Sun);
}

void AClock::UpdateTime(float DeltaSec)
{
	TotalSecond += DeltaSec * TimeScale; //DeltaSec�� TimeScale �踸ŭ ����

	//1���� 86400�� 
	CurrentDay = TotalSecond / 86400;
	int32 RemainingSecondsAfterDay = (int)TotalSecond % 86400; //���� ������ ������ �ʸ� ���
	CurrentHour = RemainingSecondsAfterDay / 3600;  // ���� �ð��� 3600 ������ '��' ������ ���
	int32 RemainingSecondsAfterHour = RemainingSecondsAfterDay % 3600; // ��, �� ������ ������ ��
	CurrentMinute = RemainingSecondsAfterHour / 60; // �ʿ��� ������ ��ȯ 
	CurrentSecond = RemainingSecondsAfterHour % 60; // ���� ������ ������ -> ���� ��
}

void AClock::RotateDirectionalLightWithTime(AActor* OwningActor)
{
	if (OwningActor)
	{
		ADirectionalLight* _DirectionalLight = Cast<ADirectionalLight>(OwningActor);
		if (_DirectionalLight)
		{
			// float _AnglePerHour = 360.0f / 24.0f; //360���� 24�ð����� ���� = 15
			//float _HourAngle = FMath::Fmod(CurrentHour * _AnglePerHour, 360.0f);
			float _HourAngle = FMath::Fmod(CurrentHour * 15, 360.0f); //�ð��� ���� ���� ���
			float _MinuteAngle = (CurrentMinute / 60.0f) * 15; //�п� ���� ���� ���
			float _SecondAngle = (CurrentMinute / 60.0f) * (15 / 60.0f); // �ʿ� ���� ���� ���
			float _CurrentAngle = _HourAngle + _MinuteAngle + _SecondAngle;

			FRotator _NewRotation = FRotator(_CurrentAngle, 0.0f, 0.0f);
			_DirectionalLight->SetActorRotation(_NewRotation); //ȸ�� ����

			UpdateSunColorByHourMinute(OwningActor);
		}
	}
}

void AClock::UpdateSunColorByHourMinute(AActor* OwningActor)
{
     //UDirectionalLightComponent�� , OwningActor�κ��� �޾ƿ� 
	UDirectionalLightComponent* _DirectionalLightComp 
	= Cast<ADirectionalLight>(OwningActor)->GetComponent();
	float _LightTime = CurrentHour + (CurrentMinute / 60);

	//�ð� ���� 24�ð� ������ ����
	_LightTime = FMath::Fmod(_LightTime,24.0f);
	float InterpolationFactor = (_LightTime - (CurrentColorIndex * 3)) / 3.0f;
	
	CurrentColorIndex = FMath::FloorToInt(_LightTime/3.0f) % SunColors.Num();
	

	if (CurrentColorIndex + 1 < SunColors.Num())
	{
		FLinearColor InterpolatedColor 
		= FLinearColor::LerpUsingHSV(SunColors[CurrentColorIndex],
			SunColors[CurrentColorIndex + 1], InterpolationFactor);

		_DirectionalLightComp->SetLightColor(InterpolatedColor);
	}
	else 
	{
		FLinearColor InterpolatedColor
			= FLinearColor::LerpUsingHSV(SunColors[CurrentColorIndex],
				SunColors[0], InterpolationFactor);

		_DirectionalLightComp->SetLightColor(InterpolatedColor);
	}

	/*
	if (_LightTime > 0 && _LightTime <= 3)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color24, Color3, _LightTime / 3.0f);
	}
	else if (_LightTime > 3 && _LightTime <= 6)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color3, Color6, _LightTime / 3.0f);
	}
	else if (_LightTime > 6 && _LightTime <= 9)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color6, Color9, _LightTime / 3.0f);
	}
	else if (_LightTime > 9 && _LightTime <= 12)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color9, Color12, _LightTime / 3.0f);
	}
	else if (_LightTime > 12 && _LightTime <= 15)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color12, Color15, _LightTime / 3.0f);
	}
	else if (_LightTime > 15 && _LightTime <= 18)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color15, Color18, _LightTime / 3.0f);
	}
	else if (_LightTime > 18 && _LightTime <= 21)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color18, Color21, _LightTime / 3.0f);
	}
	else if (_LightTime > 21 && _LightTime <= 24)
	{
		InterpolatedColor = FLinearColor::LerpUsingHSV(Color21, Color24, _LightTime / 3.0f);
	}
	*/	
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("%f, %d"), _LightTime, CurrentColorIndex));
}

FString AClock::GetTimeByTotalSec(float totalSec)
{
	// year = totalSec / ONE_YEAR;
	//month = totalSec / ONE_MONTH % 12; //1�޷� ���� ��, 12�� ���� ������ ��

	CurrentDay = (int)totalSec / ONE_DAY % 30; // 1�Ϸ� ���� ��, 30���� ���� ������ ��
	CurrentHour = (int)totalSec / ONE_HOUR % 24; // 1�ð����� ���� ��, 24�� ���� ������ �� 
	CurrentMinute = (int)totalSec / ONE_MINUTE % 60; // 1������ ���� ��, 60���� ���� ������ ��
	CurrentSecond = (int)totalSec % 60;

	FString Now;
	Now = "D: " + FString::SanitizeFloat(CurrentDay)
		+ "-H: " + FString::SanitizeFloat(CurrentHour)
		+ "-M: " + FString::SanitizeFloat(CurrentMinute)
		+ "-S: " + FString::SanitizeFloat(CurrentSecond);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, (TEXT("%s"), Now));

	return Now;
}
