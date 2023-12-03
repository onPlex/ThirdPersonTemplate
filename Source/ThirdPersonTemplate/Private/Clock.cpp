// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

#define ONE_YEAR 31104000 // 360�� ���� 1�� ��
#define ONE_MONTH 2592000 // 30�� ���� 1�� ��
#define ONE_DAY 86400 // 1�� ���� 24�ð� ��
#define ONE_HOUR 3600 // 1�ð� 24�ð� ��
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

	//GetTimeByTotalSec(TotalSeconds);
}

void AClock::UpdateTime(float DeltaSec)
{
	TotalSeconds += DeltaSec * TimeScale; // DeltaSeconds�� ���Ͽ� �ð� ������Ʈ

	CurrentDay = TotalSeconds / 86400; // 1���� 86400��
	int32 RemainingSecondsAfterDays = (int)TotalSeconds % 86400; // ���� ������ ������ �ʸ� ���
	CurrentHour = RemainingSecondsAfterDays / 3600; // �ð��� �ʿ��� �ð����� ��ȯ
	int32 RemainingSecondsAfterHours = RemainingSecondsAfterDays % 3600; // �ð��� ������ ������ ��
	CurrentMinute = RemainingSecondsAfterHours / 60; // ���� �ʿ��� ������ ��ȯ
	CurrentSecond = RemainingSecondsAfterHours % 60; // ���� ������ ������ �ʸ� �ʷ� ���
}

// Directional Light�� �����ϱ� ���� �Լ�
void AClock::RotateDirectionalLightWithTime(AActor* OwningActor) {
	if (OwningActor) {
		ADirectionalLight* _DirectionalLight = Cast<ADirectionalLight>(OwningActor);
		UDirectionalLightComponent* _DirectionalLightComp = _DirectionalLight->GetComponent();


		if (_DirectionalLight) {

			//float _AnglePerHour = 360.0f / 24.0f; // 24�ð��� 360���� ���� // = 15
			//float _HourAngle = FMath::Fmod(CurrentHour * _AnglePerHour, 360.0f); // �ð��� ���� ���� ���
			float _HourAngle = FMath::Fmod(CurrentHour * 15, 360.0f); // �ð��� ���� ���� ���
			//float _MinuteAngle = (CurrentMinute / 60.0f) * _AnglePerHour; // �п� ���� ���� ���
			float _MinuteAngle = (CurrentMinute / 60.0f) * 15; // �п� ���� ���� ���
			//float _SecondAngle = (CurrentSecond / 60.0f) * (_AnglePerHour / 60.0f); // �ʿ� ���� ���� ���
			float _SecondAngle = (CurrentSecond / 60.0f) * (15 / 60.0f); // �ʿ� ���� ���� ���
			float _CurrentAngle = _HourAngle + _MinuteAngle + _SecondAngle; // �ð�, ��, �ʿ� ���� �� ���� ���

			FRotator _NewRotation = FRotator(_CurrentAngle,0.0f , 0.0f);
			_DirectionalLight->SetActorRotation(_NewRotation); // Directional Light�� ȸ�� ����



			// �ð��� ���� �����Ǵ� ������ �����ϰ� ���� ���
			FLinearColor InterpolatedColor;

			if (CurrentHour > 0 && CurrentHour <= 3)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color24, Color3, CurrentHour / 3.0f);
			}
			else if (CurrentHour > 3 && CurrentHour <= 6)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color3, Color6, (CurrentHour-3) / 3.0f);
			}
			else if (CurrentHour > 6 && CurrentHour <= 9)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color6, Color9, (CurrentHour - 6) / 3.0f);
			}
			else if (CurrentHour > 9 && CurrentHour <= 12)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color9, Color12, (CurrentHour - 9) / 3.0f);
			}
			else if (CurrentHour > 12 && CurrentHour <= 15)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color12, Color15, (CurrentHour - 12) / 3.0f);
			}
			else if (CurrentHour > 15 && CurrentHour <= 18)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color15, Color18, (CurrentHour - 15) / 3.0f);
			}
			else if (CurrentHour > 18 && CurrentHour <= 21)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color18, Color21, (CurrentHour - 18) / 3.0f);
			}
			else if (CurrentHour > 21 && CurrentHour <= 24)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color21, Color24, (CurrentHour - 21) / 3.0f);
			}
			else
			{
				InterpolatedColor = FLinearColor::White;
			}
			
			// Directional Light�� ���� ����
			_DirectionalLightComp->SetLightColor(InterpolatedColor);
				
		}
	}
}

FString AClock::GetTimeByTotalSec(float totlaSec)
{
	//year = totlaSec / ONE_YEAR; // �Է°��� 1������ ����
	//month = totlaSec / ONE_MONTH % 12; // �� 1�޷� ���� �� 12�� ���� ��������
	CurrentDay = (int)totlaSec / ONE_DAY % 30; // �� 1������ ���� �� 30���� ���� ��������
	CurrentHour = (int)totlaSec / ONE_HOUR % 24; // �� 1�ð����� ���� �� 24�� ���� ��������
	CurrentMinute = (int)totlaSec / ONE_MINUTE % 60; // �� 1������ ���� �� 60���� ���� ��������
	CurrentSecond = (int)totlaSec % 60; // �� 60�ʷ� ���� ��������

	FString Now ;
	Now = "D:" + FString::SanitizeFloat(CurrentDay)
	+ "-H:"+ FString::SanitizeFloat(CurrentHour)
	+ "-M:"+ FString::SanitizeFloat(CurrentMinute)
	+ "-S:"+ FString::SanitizeFloat(CurrentSecond);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (TEXT("%s"), Now));
	return Now;
}

